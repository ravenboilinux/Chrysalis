#include <StdAfx.h>

#include "XMLSerializer.h"
#include "ECS/Components/Components.h"


namespace Chrysalis::ECS
{
void SaveComponent(const XmlNodeRef& node, const IComponent& component)
{
	// Create a node for the component and mark it with the hashed name so we can lookup the class on loading.
	XmlNodeRef componentNode = node->newChild(component.GetHashedName().data());

	// Serialise it to the node we just made.
	Serialization::SaveXmlNode(componentNode, Serialization::SStruct(component));
}


void LoadECSFromXML(string fileName, entt::registry& registry)
{
	// Load the file into an in-memory structure.
	if (XmlNodeRef entitiesNode = GetISystem()->LoadXmlFromFile(fileName))
	{
		// Iterate through all the children which should be individual entities.
		for (int i = 0, n = entitiesNode->getChildCount(); i < n; ++i)
		{
			// Grab the entity, which is basically an empty wrapper.
			XmlNodeRef entityNode = entitiesNode->getChild(i);

			// We should create a fresh entity for the components to attach onto.
			auto entity = registry.create();

			// Get the properties node - this holds all the properties for this component.
			if (XmlNodeRef componentsNode = entityNode->findChild("components"))
			{
				// Iterate through all the components.
				for (int i = 0, n = componentsNode->getChildCount(); i < n; ++i)
				{
					// Grab the entity, which is basically an empty wrapper.
					XmlNodeRef componentNode = componentsNode->getChild(i);

					// Using the tag as a unique ID for the class for now.
					auto hash = entt::hashed_string {componentNode->getTag()};

					// Ask the system for the class and default construct a component of that type.
					if (auto component = entt::resolve_id(hash))
					{
						// Uses the registry to construct a component, assign it to the entity, and then return a reference for us to use.
						auto any = component.construct(entity, &registry);

						// Serialise the properties across to the component.
						// TODO: I need to stop being lazy and using a base class and make this work with a templated function instead on the actual class.
						auto& iComponent = any.cast<ECS::IComponent>();

						Serialization::LoadXmlNode(iComponent, componentNode);
					}
				}
			}
		}
	}
}
}