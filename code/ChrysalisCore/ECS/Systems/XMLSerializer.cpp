#include <StdAfx.h>

#include "XMLSerializer.h"
#include "ECS/Components/Components.h"


namespace Chrysalis::ECS
{
template<typename Type>
void SaveComponent(const XmlNodeRef& node, const Type& component)
{
	// Components need a prop meta value that allows us to associate their type with a string used to serialise them.
	if (auto prop = entt::resolve<Type>().prop("name-hs"_hs))
	{
		// Create a node for the component and mark it with the hashed name so we can lookup the class on loading.
		auto hashedName = prop.value().cast<entt::hashed_string>();
		XmlNodeRef componentNode = node->newChild(hashedName.data());

		// Serialise it to the node we just made.
		Serialization::SaveXmlNode(componentNode, Serialization::SStruct(component));
	}
	else
	{
		CryLogAlways("The component's hashed name (.prop(\"name-hs\") isn't in the registry");
	}
}


//template<typename Type>
void LoadComponent(const XmlNodeRef& node, entt::hashed_string hash, entt::registry& registry, entt::entity entity)
{
	if (auto component = entt::resolve_id(hash))
	{
		//if (auto func = entt::resolve_id(hash).func("serialize"_hs))
		//{
		//	auto any = component.construct(entity, &registry);
		//	func.invoke(any, node);
		//}

		// Uses the registry to construct a default component, assign it to the entity, and then return a reference for us to use.
		auto any = component.construct(entity, &registry);
		
		// Cheating, casting it to a base class and using polymorphism to copy across the values in node to iComponent.
		auto& iComponent = any.cast<ECS::IComponent>();
		Serialization::LoadXmlNode(iComponent, node);
	}
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

					// Load em.
					// TODO: Needs to work without using a base class and polymorphism.
					LoadComponent(componentNode, hash, registry, entity);
				}
			}
		}
	}
}
}