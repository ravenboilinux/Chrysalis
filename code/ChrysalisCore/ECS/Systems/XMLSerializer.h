#pragma once


namespace Chrysalis::ECS
{
struct IComponent;

// Loads the entities and components from an XML file.
void LoadECSFromXML(string fileName, entt::registry& registry);


// Used by ECS snapshot code to handle calls to serialise each entity and component in a registry.

struct SerialiseECS
{
	// We need to create a DOM for the entities to attach onto.
	SerialiseECS()
	{
		m_entitiesNode = GetISystem()->CreateXmlNode("entities");
	}


	// ***
	// *** Input
	// ***

	// Input hasn't been implemented or tested as yet.

	/** Called for each type to announce the number of entities of that type. */
	void operator()(std::underlying_type_t<entt::entity>& count)
	{
		int a = 1;
		a++;
	}


	/** Called for each entity. */
	void operator()(entt::entity&)
	{
		int a = 1;
		a++;
	}


	/** Called for each entity and component type combination. */
	template<typename Type>
	void operator()(entt::entity& entity, Type& component)
	{
		int a = 1;
		a++;
	}

	// ***
	// *** Output
	// ***

	
	/** Called for each type to announce the number of entities of that type. */
	void operator()(std::underlying_type_t<entt::entity> count)
	{
		int a = 1;
		a++;
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