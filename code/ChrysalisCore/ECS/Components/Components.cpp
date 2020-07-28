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
		.type(ECS::IComponent().GetHashedName());

	// General.
	entt::meta<ECS::Name>()
		.base<ECS::IComponent>()
		.type(ECS::Name().GetHashedName())
		.ctor<&emplace<ECS::Name>, entt::as_ref_t>();

	entt::meta<ECS::Prototype>()
		.base<ECS::IComponent>()
		.type(ECS::Prototype().GetHashedName())
		.ctor<&emplace<ECS::Prototype>, entt::as_ref_t>();

	entt::meta<ECS::SourceAndTarget>()
		.base<ECS::IComponent>()
		.type(ECS::SourceAndTarget().GetHashedName())
		.ctor<&emplace<ECS::SourceAndTarget>, entt::as_ref_t>();

	// Health.
	entt::meta<ECS::Health>()
		.base<ECS::IComponent>()
		.type(ECS::Health().GetHashedName())
		.ctor<&emplace<ECS::Health>, entt::as_ref_t>();

	entt::meta<ECS::Damage>()
		.base<ECS::IComponent>()
		.type(ECS::Damage().GetHashedName())
		.ctor<&emplace<ECS::Damage>, entt::as_ref_t>();

	entt::meta<ECS::DamageOverTime>()
		.base<ECS::IComponent>()
		.type(ECS::DamageOverTime().GetHashedName())
		.ctor<&emplace<ECS::DamageOverTime>, entt::as_ref_t>();

	entt::meta<ECS::Heal>()
		.base<ECS::IComponent>()
		.type(ECS::Heal().GetHashedName())
		.ctor<&emplace<ECS::Heal>, entt::as_ref_t>();

	entt::meta<ECS::HealOverTime>()
		.base<ECS::IComponent>()
		.type(ECS::HealOverTime().GetHashedName())
		.ctor<&emplace<ECS::HealOverTime>, entt::as_ref_t>();

	// Qi.
	entt::meta<ECS::Qi>()
		.base<ECS::IComponent>()
		.type(ECS::Qi().GetHashedName())
		.ctor<&emplace<ECS::Qi>, entt::as_ref_t>();

	entt::meta<ECS::UtiliseQi>()
		.base<ECS::IComponent>()
		.type(ECS::UtiliseQi().GetHashedName())
		.ctor<&emplace<ECS::UtiliseQi>, entt::as_ref_t>();

	entt::meta<ECS::UtiliseQiOverTime>()
		.base<ECS::IComponent>()
		.type(ECS::UtiliseQiOverTime().GetHashedName())
		.ctor<&emplace<ECS::UtiliseQiOverTime>, entt::as_ref_t>();

	entt::meta<ECS::ReplenishQi>()
		.base<ECS::IComponent>()
		.type(ECS::ReplenishQi().GetHashedName())
		.ctor<&emplace<ECS::ReplenishQi>, entt::as_ref_t>();

	entt::meta<ECS::ReplenishQiOverTime>()
		.base<ECS::IComponent>()
		.type(ECS::ReplenishQiOverTime().GetHashedName())
		.ctor<&emplace<ECS::ReplenishQiOverTime>, entt::as_ref_t>();

	// Spell.
	entt::meta<ECS::Spell>()
		.base<ECS::IComponent>()
		.type(ECS::Spell().GetHashedName())
		.ctor<&emplace<ECS::Spell>, entt::as_ref_t>();

	// Spell actions.
	entt::meta<ECS::SpellActionSchematyc>()
		.base<ECS::IComponent>()
		.type(ECS::SpellActionSchematyc().GetHashedName())
		.ctor<&emplace<ECS::SpellActionSchematyc>, entt::as_ref_t>();

	entt::meta<ECS::SpellActionDRS>()
		.base<ECS::IComponent>()
		.type(ECS::SpellActionDRS().GetHashedName())
		.ctor<&emplace<ECS::SpellActionDRS>, entt::as_ref_t>();

	entt::meta<ECS::SpellActionInspect>()
		.base<ECS::IComponent>()
		.type(ECS::SpellActionInspect().GetHashedName())
		.ctor<&emplace<ECS::SpellActionInspect>, entt::as_ref_t>();

	entt::meta<ECS::SpellActionExamine>()
		.base<ECS::IComponent>()
		.type(ECS::SpellActionExamine().GetHashedName())
		.ctor<&emplace<ECS::SpellActionExamine>, entt::as_ref_t>();

	entt::meta<ECS::SpellActionTake>()
		.base<ECS::IComponent>()
		.type(ECS::SpellActionTake().GetHashedName())
		.ctor<&emplace<ECS::SpellActionTake>, entt::as_ref_t>();

	entt::meta<ECS::SpellActionDrop>()
		.base<ECS::IComponent>()
		.type(ECS::SpellActionDrop().GetHashedName())
		.ctor<&emplace<ECS::SpellActionDrop>, entt::as_ref_t>();

	entt::meta<ECS::SpellActionThrow>()
		.base<ECS::IComponent>()
		.type(ECS::SpellActionThrow().GetHashedName())
		.ctor<&emplace<ECS::SpellActionThrow>, entt::as_ref_t>();

	entt::meta<ECS::SpellActionSwitch>()
		.base<ECS::IComponent>()
		.type(ECS::SpellActionSwitch().GetHashedName())
		.ctor<&emplace<ECS::SpellActionSwitch>, entt::as_ref_t>();

	entt::meta<ECS::SpellActionOpen>()
		.base<ECS::IComponent>()
		.type(ECS::SpellActionOpen().GetHashedName())
		.ctor<&emplace<ECS::SpellActionOpen>, entt::as_ref_t>();

	entt::meta<ECS::SpellActionClose>()
		.base<ECS::IComponent>()
		.type(ECS::SpellActionClose().GetHashedName())
		.ctor<&emplace<ECS::SpellActionClose>, entt::as_ref_t>();

	entt::meta<ECS::SpellActionUnlock>()
		.base<ECS::IComponent>()
		.type(ECS::SpellActionUnlock().GetHashedName())
		.ctor<&emplace<ECS::SpellActionUnlock>, entt::as_ref_t>();

	entt::meta<ECS::SpellActionLock>()
		.base<ECS::IComponent>()
		.type(ECS::SpellActionLock().GetHashedName())
		.ctor<&emplace<ECS::SpellActionLock>, entt::as_ref_t>();

	// Environment.
	entt::meta<ECS::RenderLight>()
		.base<ECS::IComponent>()
		.type(ECS::RenderLight().GetHashedName())
		.ctor<&emplace<ECS::RenderLight>, entt::as_ref_t>();

	// Items.
	entt::meta<ECS::ItemClass>()
		.base<ECS::IComponent>()
		.type(ECS::ItemClass().GetHashedName())
		.ctor<&emplace<ECS::ItemClass>, entt::as_ref_t>();
}
}
