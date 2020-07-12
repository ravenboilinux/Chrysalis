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
template<typename Type>
Type& assign(const entt::entity entity, entt::registry* registry)
{
	return registry->assign<Type>(entity);
}


/** Every component needs to register itself with the meta before we can utilise it properly. */
void RegisterComponentsWithMeta()
{
	// The base component is required in order to call the .base function.
	entt::meta<ECS::IComponent>()
		.type(ECS::IComponent().GetHashedName());

	// General.
	entt::meta<ECS::Name>()
		.base<ECS::IComponent>()
		.type(ECS::Name().GetHashedName())
		.ctor<&assign<ECS::Name>, entt::as_alias_t>();

	entt::meta<ECS::Prototype>()
		.base<ECS::IComponent>()
		.type(ECS::Prototype().GetHashedName())
		.ctor<&assign<ECS::Prototype>, entt::as_alias_t>();

	entt::meta<ECS::SourceAndTarget>()
		.base<ECS::IComponent>()
		.type(ECS::SourceAndTarget().GetHashedName())
		.ctor<&assign<ECS::SourceAndTarget>, entt::as_alias_t>();

	// Health.
	entt::meta<ECS::Health>()
		.base<ECS::IComponent>()
		.type(ECS::Health().GetHashedName())
		.ctor<&assign<ECS::Health>, entt::as_alias_t>();

	entt::meta<ECS::Damage>()
		.base<ECS::IComponent>()
		.type(ECS::Damage().GetHashedName())
		.ctor<&assign<ECS::Damage>, entt::as_alias_t>();

	entt::meta<ECS::DamageOverTime>()
		.base<ECS::IComponent>()
		.type(ECS::DamageOverTime().GetHashedName())
		.ctor<&assign<ECS::DamageOverTime>, entt::as_alias_t>();

	entt::meta<ECS::Heal>()
		.base<ECS::IComponent>()
		.type(ECS::Heal().GetHashedName())
		.ctor<&assign<ECS::Heal>, entt::as_alias_t>();

	entt::meta<ECS::HealOverTime>()
		.base<ECS::IComponent>()
		.type(ECS::HealOverTime().GetHashedName())
		.ctor<&assign<ECS::HealOverTime>, entt::as_alias_t>();

	// Qi.
	entt::meta<ECS::Qi>()
		.base<ECS::IComponent>()
		.type(ECS::Qi().GetHashedName())
		.ctor<&assign<ECS::Qi>, entt::as_alias_t>();

	entt::meta<ECS::UtiliseQi>()
		.base<ECS::IComponent>()
		.type(ECS::UtiliseQi().GetHashedName())
		.ctor<&assign<ECS::UtiliseQi>, entt::as_alias_t>();

	entt::meta<ECS::UtiliseQiOverTime>()
		.base<ECS::IComponent>()
		.type(ECS::UtiliseQiOverTime().GetHashedName())
		.ctor<&assign<ECS::UtiliseQiOverTime>, entt::as_alias_t>();

	entt::meta<ECS::ReplenishQi>()
		.base<ECS::IComponent>()
		.type(ECS::ReplenishQi().GetHashedName())
		.ctor<&assign<ECS::ReplenishQi>, entt::as_alias_t>();

	entt::meta<ECS::ReplenishQiOverTime>()
		.base<ECS::IComponent>()
		.type(ECS::ReplenishQiOverTime().GetHashedName())
		.ctor<&assign<ECS::ReplenishQiOverTime>, entt::as_alias_t>();

	// Spell.
	entt::meta<ECS::Spell>()
		.base<ECS::IComponent>()
		.type(ECS::Spell().GetHashedName())
		.ctor<&assign<ECS::Spell>, entt::as_alias_t>();

	// Spell actions.
	//entt::meta<ECS::SpellActionOpenDoor>()
	//	.base<ECS::IComponent>()
	//	.type(ECS::SpellActionOpenDoor().GetHashedName())
	//	.ctor<&assign<ECS::SpellActionOpenDoor>, entt::as_alias_t>();

	// Spell actions.
	entt::meta<ECS::SpellActionSchematyc>()
		.base<ECS::IComponent>()
		.type(ECS::SpellActionSchematyc().GetHashedName())
		.ctor<&assign<ECS::SpellActionSchematyc>, entt::as_alias_t>();

	entt::meta<ECS::SpellActionDRS>()
		.base<ECS::IComponent>()
		.type(ECS::SpellActionDRS().GetHashedName())
		.ctor<&assign<ECS::SpellActionDRS>, entt::as_alias_t>();

	entt::meta<ECS::SpellActionInspect>()
		.base<ECS::IComponent>()
		.type(ECS::SpellActionInspect().GetHashedName())
		.ctor<&assign<ECS::SpellActionInspect>, entt::as_alias_t>();

	entt::meta<ECS::SpellActionExamine>()
		.base<ECS::IComponent>()
		.type(ECS::SpellActionExamine().GetHashedName())
		.ctor<&assign<ECS::SpellActionExamine>, entt::as_alias_t>();

	entt::meta<ECS::SpellActionTake>()
		.base<ECS::IComponent>()
		.type(ECS::SpellActionTake().GetHashedName())
		.ctor<&assign<ECS::SpellActionTake>, entt::as_alias_t>();

	entt::meta<ECS::SpellActionDrop>()
		.base<ECS::IComponent>()
		.type(ECS::SpellActionDrop().GetHashedName())
		.ctor<&assign<ECS::SpellActionDrop>, entt::as_alias_t>();

	entt::meta<ECS::SpellActionThrow>()
		.base<ECS::IComponent>()
		.type(ECS::SpellActionThrow().GetHashedName())
		.ctor<&assign<ECS::SpellActionThrow>, entt::as_alias_t>();

	entt::meta<ECS::SpellActionSwitch>()
		.base<ECS::IComponent>()
		.type(ECS::SpellActionSwitch().GetHashedName())
		.ctor<&assign<ECS::SpellActionSwitch>, entt::as_alias_t>();

	entt::meta<ECS::SpellActionOpen>()
		.base<ECS::IComponent>()
		.type(ECS::SpellActionOpen().GetHashedName())
		.ctor<&assign<ECS::SpellActionOpen>, entt::as_alias_t>();

	entt::meta<ECS::SpellActionClose>()
		.base<ECS::IComponent>()
		.type(ECS::SpellActionClose().GetHashedName())
		.ctor<&assign<ECS::SpellActionClose>, entt::as_alias_t>();

	entt::meta<ECS::SpellActionUnlock>()
		.base<ECS::IComponent>()
		.type(ECS::SpellActionUnlock().GetHashedName())
		.ctor<&assign<ECS::SpellActionUnlock>, entt::as_alias_t>();

	entt::meta<ECS::SpellActionLock>()
		.base<ECS::IComponent>()
		.type(ECS::SpellActionLock().GetHashedName())
		.ctor<&assign<ECS::SpellActionLock>, entt::as_alias_t>();

	// Environment.
	entt::meta<ECS::RenderLight>()
		.base<ECS::IComponent>()
		.type(ECS::RenderLight().GetHashedName())
		.ctor<&assign<ECS::RenderLight>, entt::as_alias_t>();

	// Items.
	entt::meta<ECS::ItemClass>()
		.base<ECS::IComponent>()
		.type(ECS::ItemClass().GetHashedName())
		.ctor<&assign<ECS::ItemClass>, entt::as_alias_t>();
}
}
