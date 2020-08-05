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
		if (isFirstTime)
		{
			isFirstTime = false;
			count = m_entitiesNode->getChildCount();
		}
		else
		{
			if (auto node = m_componentTypeNode->getChild(m_currentChild))
			{
				// Dirty way to get the attribute out, since I don't have a primitive for getting an entity attribute.
				std::underlying_type_t<entt::entity> val {0};
				node->getAttr("count", val);
				count = val;

			}
			
			m_currentType++;
		}	
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
		//if (XmlNodeRef componentsNode = entityNode->findChild("components"))
		{
			if (auto prop = entt::resolve<Type>().prop("name-hs"_hs))
			{
				auto hashedName = prop.value().cast<entt::hashed_string>();
				if (XmlNodeRef node = entityNode->findChild(hashedName.data()))
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
		isFirstTime = true;

		if (m_essNode = GetISystem()->LoadXmlFromFile(fileName))
		{
			m_entitiesNode = m_essNode->findChild("entities");
			m_componentsNode = m_essNode->findChild("components");
			m_componentTypeNode = m_componentsNode->findChild("component-types");

			m_currentType = 0;
			m_currentChild = 0;
		}
	}

private:
	bool isFirstTime {true};
	XmlNodeRef m_essNode;
	XmlNodeRef m_entitiesNode;
	XmlNodeRef m_componentsNode;
	XmlNodeRef m_componentTypeNode;
	std::underlying_type_t<entt::entity> m_currentType {0};
	std::underlying_type_t<entt::entity> m_currentChild {0};
};


// Used by ECS snapshot code to handle calls to serialise each entity and component in a registry.

struct SerialiseECSOutput
{
	// We need to create a DOM for the entities to attach onto.
	SerialiseECSOutput()
	{
		m_essNode = GetISystem()->CreateXmlNode("ecs");
		if (m_essNode)
		{
			// Node for all the component types.
			m_entitiesNode = m_essNode->newChild("entities");
			m_componentsNode = m_essNode->newChild("components");
			m_componentTypeNode = m_componentsNode->newChild("component-types");

			// Create a meta node if one doesn't exist.
			m_metaNode = m_essNode->newChild("meta");
			m_metaComponentTypesNode = m_metaNode->newChild("component-types");
		}
	}


	// ***
	// *** Output
	// ***


	/** Called for each type to announce the number of entities of that type. */
	void operator()(std::underlying_type_t<entt::entity> count)
	{
		if (isFirstTime)
		{
			entityInstances = count;
			isFirstTime = false;

			if (m_metaNode)
			{
				// Each entity get's a couple of nodes made for storing it's components.
				XmlNodeRef node = m_metaNode->newChild("component-type-total");

				// This static cast should be fine with common underlying types.
				node->setAttr("count", static_cast<std::underlying_type_t<entt::entity>>(count));
			}
		}
		else
		{
			componentInstances.push_back(count);
			if (m_metaComponentTypesNode)
			{
				// Each entity get's a couple of nodes made for storing it's components.
				XmlNodeRef node = m_componentTypeNode->newChild("component-type");

				// This static cast should be fine with common underlying types.
				node->setAttr("count", static_cast<std::underlying_type_t<entt::entity>>(count));
				node->setAttr("typeId", static_cast<int>(componentInstances.size() - 1));
			}
		}
	}


	/** Called for each entity. */
	void operator()(entt::entity entity)
	{
		if (m_essNode)
		{
			// Each entity get's a couple of nodes made for storing it's components.
			XmlNodeRef entityNode = m_entitiesNode->newChild("entity");

			// This static cast should be fine with common underlying types.
			entityNode->setAttr("entityId", static_cast<std::underlying_type_t<entt::entity>>(entity));
		}
	}


	/** Called for each entity and component type combination. */
	template<typename Type>
	void operator()(entt::entity entity, const Type& component)
	{
		// Each entity get's a couple of nodes made for storing it's components.
		XmlNodeRef componentsNode = m_entitiesNode->getChild(static_cast<std::underlying_type_t<entt::entity>>(entity));
		if (componentsNode)
		{
			//SaveComponent(m_essNode, entity, component);
			SaveComponent(componentsNode, entity, component);
		}
	}


	void SaveToFile(string fileName)
	{
		isFirstTime = true;

		componentInstances.clear();
		entityInstances = 0;
		m_essNode->saveToFile(fileName);
	}

private:
	bool isFirstTime {true};
	std::underlying_type_t<entt::entity> entityInstances {0};
	std::vector<std::underlying_type_t<entt::entity>> componentInstances;
	XmlNodeRef m_essNode;
	XmlNodeRef m_entitiesNode;
	XmlNodeRef m_componentsNode;
	XmlNodeRef m_componentTypeNode;
	XmlNodeRef m_metaEntitiesNode;
	XmlNodeRef m_metaNode;
	XmlNodeRef m_metaComponentTypesNode;
};
}