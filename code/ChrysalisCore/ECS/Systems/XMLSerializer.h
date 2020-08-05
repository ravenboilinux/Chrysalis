#pragma once


namespace Chrysalis::ECS
{
struct IComponent;

// Loads the entities and components from an XML file.
void LoadECSFromXML(string fileName, entt::registry& registry);


// Used by ECS snapshot code to handle calls to serialise each entity and component in a registry.

struct SerialiseECSInput
{
	// We need to create a DOM for the entities to attach onto.
	SerialiseECSInput()
	{
	}


	// ***
	// *** Input
	// ***

	/** Called for each type to announce the number of entities of that type. */
	void operator()(std::underlying_type_t<entt::entity>& count)
	{
		count = m_entitiesNode->getChildCount();

		m_currentChild = 0;
	}


	/** Called for each entity. */
	void operator()(entt::entity& entity)
	{
		// Each entity get's a couple of nodes made for storing it's components.
		XmlNodeRef entityNode = m_entitiesNode->getChild(m_currentChild);

		// Dirty way to get the attribute out, since I don't have a primitive for getting an entity attribute.
		std::underlying_type_t<entt::entity> val {0};
		entityNode->getAttr("entityId", val);
		entity = static_cast<entt::entity>(val);

		m_currentChild++;
	}


	/** Called for each entity and component type combination. */
	template<typename Type>
	void operator()(entt::entity& entity, Type& component)
	{
		// HACK: Make the entityId be the next in sequence.
		entity = static_cast<entt::entity>(m_currentChild);

		// Each entity get's a couple of nodes made for storing it's components.
		XmlNodeRef entityNode = m_entitiesNode->getChild(m_currentChild);
		if (XmlNodeRef componentsNode = entityNode->findChild("components"))
		{
			if (auto prop = entt::resolve<Type>().prop("name-hs"_hs))
			{
				auto hashedName = prop.value().cast<entt::hashed_string>();
				if (XmlNodeRef node = componentsNode->findChild(hashedName.data()))
				{
					LoadComponent(node, component);
				}
			}
		}
		
		// Next entity.
		m_currentChild++;
	}


	void LoadFromFile(string fileName)
	{
		if (m_entitiesNode = GetISystem()->LoadXmlFromFile(fileName))
		{
			m_currentChild = 0;
		}
	}

private:
	XmlNodeRef m_entitiesNode;
	std::map<entt::entity, XmlNodeRef> m_nodeMap;
	std::underlying_type_t<entt::entity> m_currentChild {0};
};


// Used by ECS snapshot code to handle calls to serialise each entity and component in a registry.

struct SerialiseECSOutput
{
	// We need to create a DOM for the entities to attach onto.
	SerialiseECSOutput()
	{
		m_entitiesNode = GetISystem()->CreateXmlNode("entities");
	}


	// ***
	// *** Output
	// ***


	/** Called for each type to announce the number of entities of that type. */
	void operator()(std::underlying_type_t<entt::entity>)
	{
	}


	/** Called for each entity. */
	void operator()(entt::entity entity)
	{
		if (m_entitiesNode)
		{
			// Each entity get's a couple of nodes made for storing it's components.
			XmlNodeRef entityNode = m_entitiesNode->newChild("entity");
			XmlNodeRef componentsNode = entityNode->newChild("components");

			// This static cast should be fine with common underlying types.
			entityNode->setAttr("entityId", static_cast<std::underlying_type_t<entt::entity>>(entity));

			// Store a copy in a map to enable fast lookup when iterating the components.
			m_nodeMap[entity] = componentsNode;
		}
	}


	/** Called for each entity and component type combination. */
	template<typename Type>
	void operator()(entt::entity entity, const Type& component)
	{
		// Grab the components node from the map and then inject the component into the XML DOM.
		if (XmlNodeRef componentsNode = m_nodeMap[entity])
		{
			SaveComponent(componentsNode, component);
		}
	}


	void SaveToFile(string fileName)
	{
		m_entitiesNode->saveToFile(fileName);
	}

private:
	XmlNodeRef m_entitiesNode;
	std::map<entt::entity, XmlNodeRef> m_nodeMap;
};
}