#include <StdAfx.h>

#include <ECS/Components/Components.h>
#include "CrySerialization/Enum.h"
#include "ECS/Components/Health.h"
#include "ECS/Components/Inventory.h"
#include "ECS/Components/Items.h"
#include "ECS/Components/Qi.h"
#include "ECS/Components/RenderLight.h"
#include "ECS/Components/Spells/Spell.h"
#include "ECS/Components/Spells/SpellActions.h"


namespace Chrysalis::ECS
{
// Use a registry to create a new instance of a type, assign it to an entity, and then return a reference to that instance.
// HACK: TODO: Is there a better way of handling this now with the new updated EnTT?
template<typename Type>
Type& emplace(const entt::entity entity, entt::registry* registry)
{
	return registry->emplace<Type>(entity);
}


/** Every component needs to register itself with the meta before we can utilise it properly. */
void RegisterComponentsWithMeta()
{
	// The base component is required in order to call the .base function.
	entt::meta<ECS::IComponent>()
		.type("icomponent"_hs);
//	.type(""_hs);

	// General.
	entt::meta<ECS::Name>()
		.base<ECS::IComponent>()
		.type("name"_hs)
		.prop("name-hs"_hs, "name"_hs)
		//.func<&ECS::Name::Serialize>("serialize"_hs)
		.ctor<&emplace<ECS::Name>, entt::as_ref_t>();

	entt::meta<ECS::Prototype>()
		.base<ECS::IComponent>()
		.type("prototype"_hs)
		.prop("name-hs"_hs, "prototype"_hs)
		.ctor<&emplace<ECS::Prototype>, entt::as_ref_t>();

	entt::meta<ECS::SourceAndTarget>()
		.base<ECS::IComponent>()
		.type("source-and-target"_hs)
		.prop("name-hs"_hs, "source-and-target"_hs)
		.ctor<&emplace<ECS::SourceAndTarget>, entt::as_ref_t>();

	// Health.
	entt::meta<ECS::Health>()
		.base<ECS::IComponent>()
		.type("health"_hs)
		.prop("name-hs"_hs, "health"_hs)
		.ctor<&emplace<ECS::Health>, entt::as_ref_t>();

	entt::meta<ECS::Damage>()
		.base<ECS::IComponent>()
		.type("damage"_hs)
		.prop("name-hs"_hs, "damage"_hs)
		.ctor<&emplace<ECS::Damage>, entt::as_ref_t>();

	entt::meta<ECS::DamageOverTime>()
		.base<ECS::IComponent>()
		.type("damage-over-time"_hs)
		.prop("name-hs"_hs, "damage-over-time"_hs)
		.ctor<&emplace<ECS::DamageOverTime>, entt::as_ref_t>();

	entt::meta<ECS::Heal>()
		.base<ECS::IComponent>()
		.type("heal"_hs)
		.prop("name-hs"_hs, "heal"_hs)
		.ctor<&emplace<ECS::Heal>, entt::as_ref_t>();

	entt::meta<ECS::HealOverTime>()
		.base<ECS::IComponent>()
		.type("heal-over-time"_hs)
		.prop("name-hs"_hs, "heal-over-time"_hs)
		.ctor<&emplace<ECS::HealOverTime>, entt::as_ref_t>();

	// Qi.
	entt::meta<ECS::Qi>()
		.base<ECS::IComponent>()
		.type("qi"_hs)
		.prop("name-hs"_hs, "qi"_hs)
		.ctor<&emplace<ECS::Qi>, entt::as_ref_t>();

	entt::meta<ECS::UtiliseQi>()
		.base<ECS::IComponent>()
		.type("utilise-qi"_hs)
		.prop("name-hs"_hs, "utilise-qi"_hs)
		.ctor<&emplace<ECS::UtiliseQi>, entt::as_ref_t>();

	entt::meta<ECS::UtiliseQiOverTime>()
		.base<ECS::IComponent>()
		.type("utilise-qi-over-time"_hs)
		.prop("name-hs"_hs, "utilise-qi-over-time"_hs)
		.ctor<&emplace<ECS::UtiliseQiOverTime>, entt::as_ref_t>();

	entt::meta<ECS::ReplenishQi>()
		.base<ECS::IComponent>()
		.type("replenish-qi"_hs)
		.prop("name-hs"_hs, "replenish-qi"_hs)
		.ctor<&emplace<ECS::ReplenishQi>, entt::as_ref_t>();

	entt::meta<ECS::ReplenishQiOverTime>()
		.base<ECS::IComponent>()
		.type("replenish-qi-over-time"_hs)
		.prop("name-hs"_hs, "replenish-qi-over-time"_hs)
		.ctor<&emplace<ECS::ReplenishQiOverTime>, entt::as_ref_t>();

	// Spell.
	entt::meta<ECS::Spell>()
		.base<ECS::IComponent>()
		.type("spell"_hs)
		.prop("name-hs"_hs, "spell"_hs)
		.ctor<&emplace<ECS::Spell>, entt::as_ref_t>();

	entt::meta<ECS::SpellcastExecution>()
		.base<ECS::IComponent>()
		.type("spellcast-execution"_hs)
		.prop("name-hs"_hs, "spellcast-execution"_hs)
		.ctor<&emplace<ECS::SpellcastExecution>, entt::as_ref_t>();

	// Spell actions.
	entt::meta<ECS::SpellActionSchematyc>()
		.base<ECS::IComponent>()
		.type("schematyc"_hs)
		.prop("name-hs"_hs, "schematyc"_hs)
		.ctor<&emplace<ECS::SpellActionSchematyc>, entt::as_ref_t>();

	entt::meta<ECS::SpellActionDRS>()
		.base<ECS::IComponent>()
		.type("drs"_hs)
		.prop("name-hs"_hs, "drs"_hs)
		.ctor<&emplace<ECS::SpellActionDRS>, entt::as_ref_t>();

	entt::meta<ECS::SpellActionInspect>()
		.base<ECS::IComponent>()
		.type("inspect"_hs)
		.prop("name-hs"_hs, "inspect"_hs)
		.ctor<&emplace<ECS::SpellActionInspect>, entt::as_ref_t>();

	entt::meta<ECS::SpellActionExamine>()
		.base<ECS::IComponent>()
		.type("examine"_hs)
		.prop("name-hs"_hs, "examine"_hs)
		.ctor<&emplace<ECS::SpellActionExamine>, entt::as_ref_t>();

	entt::meta<ECS::SpellActionTake>()
		.base<ECS::IComponent>()
		.type("take"_hs)
		.prop("name-hs"_hs, "take"_hs)
		.ctor<&emplace<ECS::SpellActionTake>, entt::as_ref_t>();

	entt::meta<ECS::SpellActionDrop>()
		.base<ECS::IComponent>()
		.type("drop"_hs)
		.prop("name-hs"_hs, "drop"_hs)
		.ctor<&emplace<ECS::SpellActionDrop>, entt::as_ref_t>();

	entt::meta<ECS::SpellActionThrow>()
		.base<ECS::IComponent>()
		.type("throw"_hs)
		.prop("name-hs"_hs, "throw"_hs)
		.ctor<&emplace<ECS::SpellActionThrow>, entt::as_ref_t>();

	entt::meta<ECS::SpellActionSwitch>()
		.base<ECS::IComponent>()
		.type("switch"_hs)
		.prop("name-hs"_hs, "switch"_hs)
		.ctor<&emplace<ECS::SpellActionSwitch>, entt::as_ref_t>();

	entt::meta<ECS::SpellActionOpen>()
		.base<ECS::IComponent>()
		.type("open"_hs)
		.prop("name-hs"_hs, "open"_hs)
		.ctor<&emplace<ECS::SpellActionOpen>, entt::as_ref_t>();

	entt::meta<ECS::SpellActionClose>()
		.base<ECS::IComponent>()
		.type("close"_hs)
		.prop("name-hs"_hs, "close"_hs)
		.ctor<&emplace<ECS::SpellActionClose>, entt::as_ref_t>();

	entt::meta<ECS::SpellActionUnlock>()
		.base<ECS::IComponent>()
		.type("unlock"_hs)
		.prop("name-hs"_hs, "unlock"_hs)
		.ctor<&emplace<ECS::SpellActionUnlock>, entt::as_ref_t>();

	entt::meta<ECS::SpellActionLock>()
		.base<ECS::IComponent>()
		.type("lock"_hs)
		.prop("name-hs"_hs, "lock"_hs)
		.ctor<&emplace<ECS::SpellActionLock>, entt::as_ref_t>();

	// Environment.
	entt::meta<ECS::RenderLight>()
		.base<ECS::IComponent>()
		.type("render-light"_hs)
		.prop("name-hs"_hs, "render-light"_hs)
		.ctor<&emplace<ECS::RenderLight>, entt::as_ref_t>();

	// Items.
	entt::meta<ECS::ItemClass>()
		.base<ECS::IComponent>()
		.type("item-class"_hs)
		.prop("name-hs"_hs, "item-class"_hs)
		.ctor<&emplace<ECS::ItemClass>, entt::as_ref_t>();


	// TODO: Add tags...this is enough to register one, but I don't like the way it repeats the hash name in the .type
	// It also breaks on loading thanks to not being derived from IComponent - need to see if there is a way to remove that base class.
	entt::meta<ECS::CrowdControlNone>()
		//.base<ECS::IComponent>()
		.type("crowd-control-none"_hs)
		.prop("name-hs"_hs, "crowd-control-none"_hs);
}
}
