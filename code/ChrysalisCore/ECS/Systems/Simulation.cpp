#include <StdAfx.h>

#include "Simulation.h"
#include "Systems.h"
#include "ECS/Components/Components.h"
#include "ECS/Components/Health.h"
#include "ECS/Components/Inventory.h"
#include "ECS/Components/Items.h"
#include "ECS/Components/Qi.h"
#include "ECS/Components/RenderLight.h"
#include "ECS/Components/Spells/Spell.h"
#include "ECS/Components/Spells/SpellActions.h"
#include "ECS/Systems/Systems.h"
#include "ECS/Systems/XMLSerializer.h"
#include <entt/entt.hpp>
#include "Crymath/Random.h"


namespace Chrysalis::ECS
{
template<typename Type>
void CloneComponent(const entt::registry& sourceRegistry, const entt::entity sourceEntity, entt::registry& targetRegistry, const entt::entity targetEntity)
{
	targetRegistry.emplace_or_replace<Type>(targetEntity, sourceRegistry.get<Type>(sourceEntity));
}


/** Takes a reference to a spell and applies the needed fixups. This is mainly going to fix up the source and targets
	for now. */
void CSimulation::RewireSpell(entt::registry& registry, entt::entity spellEntity, entt::entity sourceEntity, entt::entity targetEntity,
	EntityId crySourceEntityId, EntityId cryTargetEntityId)
{
	ECS::Spell& spell = registry.get<ECS::Spell>(spellEntity);

	entt::entity source {entt::null};
	entt::entity target {entt::null};
	EntityId sourceEntityId {INVALID_ENTITYID};
	EntityId targetEntityId {INVALID_ENTITYID};

	// The source should almost always be the real source of the spell.
	if (spell.sourceTargetType != ECS::TargetType::none)
	{
		source = sourceEntity;
		sourceEntityId = crySourceEntityId;
	}
	else
	{
		source = entt::null;
		sourceEntityId = INVALID_ENTITYID;
	}

	switch (spell.targetTargetType)
	{
		// Targetting the caster.
		case ECS::TargetType::self:
			target = sourceEntity;
			targetEntityId = crySourceEntityId;
			break;

			// Not targetted at an entity.
		case ECS::TargetType::none:
		case ECS::TargetType::cone:
		case ECS::TargetType::column:
		case ECS::TargetType::sourceBasedAOE:
		case ECS::TargetType::groundTargettedAOE:
			target = entt::null;
			targetEntityId = INVALID_ENTITYID;
			break;

			// Targetting the selected entity.
		default:
			target = targetEntity;
			targetEntityId = cryTargetEntityId;
			break;
	}

	// The source and target for the spell need to be added to the entity.
	registry.emplace<ECS::SourceAndTarget>(spellEntity, source, target, sourceEntityId, targetEntityId);

	// TODO: Do we really need a set of custom rewires on top of the ones for source and target?
	// Delete this code if it's not needed.

	//auto& spell = registry.get<ECS::Spell>(spellEntity);
	//switch (spell.spellRewire)
	//{
	//case ECS::SpellRewire::custom:
	//	break;

	//default:
	//	break;
	//}
}


/** Super dirty and slow way to locate a spell from the registry. */
entt::entity CSimulation::GetSpellByName(const char* spellName)
{
	auto view = m_spellRegistry.view<ECS::Name>();

	for (auto& entity : view)
	{
		auto& name = view.get<ECS::Name>(entity);

		if (strcmp(name.name, spellName) == 0)
		{
			return entity;
		}
	}

	// Failed to find it.
	return entt::null;
}


/** Queues a spell onto the actor registry - where it will later be processed by the systems. */
void CSimulation::CastSpellByName(const char* spellName, entt::entity sourceEntity, entt::entity targetEntity,
	EntityId crySourceEntityId, EntityId cryTargetEntityId)
{
	auto spellEntity = GetSpellByName(spellName);
	if (spellEntity != entt::null)
	{
		auto newEntity = m_actorRegistry.create();

		m_spellRegistry.visit(spellEntity, [this, spellEntity, newEntity](const auto type_id)
			{ stampFunctionMap[type_id](m_spellRegistry, spellEntity, m_actorRegistry, newEntity); });

		// Do fixups.
		RewireSpell(m_actorRegistry, newEntity, sourceEntity, targetEntity, crySourceEntityId, cryTargetEntityId);
	}
}


const entt::entity GetHero(entt::registry& registry)
{
	auto view = registry.view<ECS::Name>();

	for (auto& entity : view)
	{
		auto& name = view.get<ECS::Name>(entity);

		if (strcmp(name.name, "Hero") == 0)
		{
			return entity;
		}
	}

	// Failed to find it.
	return entt::null;
}


const entt::entity GetVillain(entt::registry& registry)
{
	auto view = registry.view<ECS::Name>();

	for (auto& entity : view)
	{
		auto& name = view.get<ECS::Name>(entity);

		if (strcmp(name.name, "Villain") == 0)
		{
			return entity;
		}
	}

	// Failed to find it.
	return entt::null;
}


void CSimulation::Init()
{
	ECS::RegisterComponentsWithMeta();

	// TODO: This is bound to be a point of failure, as new components which are registered do not get added to this list.
	// Need to find a way to do this closer to the registration code.
	
	// The base component is required in order to call the .base function.
	stampFunctionMap[entt::type_info<ECS::IComponent>::id()] = &CloneComponent<ECS::IComponent>;

	// General.
	stampFunctionMap[entt::type_info<ECS::Name>::id()] = &CloneComponent<ECS::Name>;
	stampFunctionMap[entt::type_info<ECS::Prototype>::id()] = &CloneComponent<ECS::Prototype>;
	stampFunctionMap[entt::type_info<ECS::SourceAndTarget>::id()] = &CloneComponent<ECS::SourceAndTarget>;

	// Health.
	stampFunctionMap[entt::type_info<ECS::Health>::id()] = &CloneComponent<ECS::Health>;
	stampFunctionMap[entt::type_info<ECS::Damage>::id()] = &CloneComponent<ECS::Damage>;
	stampFunctionMap[entt::type_info<ECS::DamageOverTime>::id()] = &CloneComponent<ECS::DamageOverTime>;
	stampFunctionMap[entt::type_info<ECS::Heal>::id()] = &CloneComponent<ECS::Heal>;
	stampFunctionMap[entt::type_info<ECS::HealOverTime>::id()] = &CloneComponent<ECS::HealOverTime>;

	// Qi.
	stampFunctionMap[entt::type_info<ECS::Qi>::id()] = &CloneComponent<ECS::Qi>;
	stampFunctionMap[entt::type_info<ECS::UtiliseQi>::id()] = &CloneComponent<ECS::UtiliseQi>;
	stampFunctionMap[entt::type_info<ECS::UtiliseQiOverTime>::id()] = &CloneComponent<ECS::UtiliseQiOverTime>;
	stampFunctionMap[entt::type_info<ECS::ReplenishQi>::id()] = &CloneComponent<ECS::ReplenishQi>;
	stampFunctionMap[entt::type_info<ECS::ReplenishQiOverTime>::id()] = &CloneComponent<ECS::ReplenishQiOverTime>;

	// Spell.
	stampFunctionMap[entt::type_info<ECS::Spell>::id()] = &CloneComponent<ECS::Spell>;

	// Spell actions.
	stampFunctionMap[entt::type_info<ECS::SpellActionSchematyc>::id()] = &CloneComponent<ECS::SpellActionSchematyc>;
	stampFunctionMap[entt::type_info<ECS::SpellActionDRS>::id()] = &CloneComponent<ECS::SpellActionDRS>;
	stampFunctionMap[entt::type_info<ECS::SpellActionInspect>::id()] = &CloneComponent<ECS::SpellActionInspect>;
	stampFunctionMap[entt::type_info<ECS::SpellActionExamine>::id()] = &CloneComponent<ECS::SpellActionExamine>;
	stampFunctionMap[entt::type_info<ECS::SpellActionTake>::id()] = &CloneComponent<ECS::SpellActionTake>;
	stampFunctionMap[entt::type_info<ECS::SpellActionDrop>::id()] = &CloneComponent<ECS::SpellActionDrop>;
	stampFunctionMap[entt::type_info<ECS::SpellActionThrow>::id()] = &CloneComponent<ECS::SpellActionThrow>;
	stampFunctionMap[entt::type_info<ECS::SpellActionSwitch>::id()] = &CloneComponent<ECS::SpellActionSwitch>;
	stampFunctionMap[entt::type_info<ECS::SpellActionOpen>::id()] = &CloneComponent<ECS::SpellActionOpen>;
	stampFunctionMap[entt::type_info<ECS::SpellActionClose>::id()] = &CloneComponent<ECS::SpellActionClose>;
	stampFunctionMap[entt::type_info<ECS::SpellActionUnlock>::id()] = &CloneComponent<ECS::SpellActionUnlock>;
	stampFunctionMap[entt::type_info<ECS::SpellActionLock>::id()] = &CloneComponent<ECS::SpellActionLock>;

	// Environment.
	stampFunctionMap[entt::type_info<ECS::RenderLight>::id()] = &CloneComponent<ECS::RenderLight>;

	// Items.
	stampFunctionMap[entt::type_info<ECS::ItemClass>::id()] = &CloneComponent<ECS::ItemClass>;
}


void CSimulation::Update(const float deltaTime)
{
	// Run the ticks no more often than this interval.
	static const float tickInterval {0.5f};

	// Track the amount of time that has gone since we last run the tick code.
	static float passedTime {0.0f};

	// Update the things which should be handled immediately e.g direct damage and heals.
	UpdateImmediate(deltaTime);

	// Check if we need to tick.
	passedTime += deltaTime;
	if (passedTime >= tickInterval)
	{
		// Perform a tick.
		// HACK: NOTE: This is just an approximation of how much time has passed. It will always be out by almost a frame's
		// worth of time. For now, it appears better to have the tick nice and steady, even if it lags behind reality a bit.
		UpdateTick(tickInterval);

		// HACK: We decrement by the interval size, so it will catch up if we miss some frames.
		passedTime -= tickInterval;
	}

	// Update the spell casts.
	UpdateWorldSpellcasts(deltaTime);
}


void CSimulation::UpdateImmediate(const float deltaTime)
{
	// Simluate some direct heals and direct damage.
	ECS::SystemApplyDamage(m_actorRegistry);
	ECS::SystemApplyHeal(m_actorRegistry);
	ECS::SystemHealthCheck(m_actorRegistry);

	// Simluate some direct qi use and replenishment.
	ECS::SystemApplyQiUtilisation(m_actorRegistry);
	ECS::SystemApplyQiReplenishment(m_actorRegistry);
}


void CSimulation::UpdateTick(const float deltaTime)
{
	// Health ticks.
	ECS::SystemApplyDamageOverTime(deltaTime, m_actorRegistry);
	ECS::SystemApplyHealOverTime(deltaTime, m_actorRegistry);
	ECS::SystemHealthCheck(m_actorRegistry);

	// Qi ticks.
	ECS::SystemApplyQiUtilisationOverTime(deltaTime, m_actorRegistry);
	ECS::SystemApplyQiReplenishmentOverTime(deltaTime, m_actorRegistry);
}


void CSimulation::UpdateWorldSpellcasts(const float deltaTime)
{
	ECS::SystemWorldSpellCasts(deltaTime, m_actorRegistry);
}


void CSimulation::LoadSimulationData()
{
	//update(10, saveRegistry);
	//update(saveRegistry);

	// Load the actor registry.
	ECS::LoadECSFromXML("chrysalis/parameters/items/test.xml", m_actorRegistry);

	// Load the spell registry.
	ECS::LoadECSFromXML("chrysalis/parameters/spells/spells.xml", m_spellRegistry);

	//auto villain = GetVillain(m_actorRegistry);
	//auto hero = GetHero(m_actorRegistry);
	//if ((hero != entt::null) && (villain != entt::null))
	//{
	//	// Health test data.
	//	TestAddDamage(hero, villain, m_actorRegistry);
	//	TestAddDamageOverTime(hero, villain, m_actorRegistry);
	//	TestAddHeal(hero, villain, m_actorRegistry);
	//	TestAddHealOverTime(hero, villain, m_actorRegistry);

	//	// Qi test data.
	//	TestAddUtiliseQi(hero, villain, m_actorRegistry);
	//	TestAddUtiliseQiOverTime(hero, villain, m_actorRegistry);
	//	TestAddReplenishQi(hero, villain, m_actorRegistry);
	//	TestAddReplenishQiOverTime(hero, villain, m_actorRegistry);
	//}
}


void CSimulation::SaveSimulationData()
{
	// Actor related.
	ECS::SerialiseECS actorSerial;

	entt::snapshot {m_actorRegistry}
		.entities(actorSerial)
		.component<ECS::Name, ECS::Prototype,
		ECS::Health, ECS::Damage, ECS::DamageOverTime, ECS::Heal, ECS::HealOverTime,
		ECS::Qi, ECS::UtiliseQi, ECS::UtiliseQiOverTime, ECS::ReplenishQi, ECS::ReplenishQiOverTime,
		ECS::Spell,
		ECS::ItemClass,
		ECS::RenderLight>(actorSerial);
	actorSerial.SaveToFile("chrysalis/parameters/items/test_out_snapshot.xml");

	// Spell prototypes.
	ECS::SerialiseECS spellSerial;

	entt::snapshot {m_spellRegistry}
		.entities(spellSerial)
		.component < ECS::Name, ECS::Prototype,
		ECS::Health, ECS::Damage, ECS::DamageOverTime, ECS::Heal, ECS::HealOverTime,
		ECS::Qi, ECS::UtiliseQi, ECS::UtiliseQiOverTime, ECS::ReplenishQi, ECS::ReplenishQiOverTime,
		ECS::Spell,
		ECS::SpellActionSchematyc, ECS::SpellActionDRS,
		ECS::SpellActionInspect, ECS::SpellActionExamine,
		ECS::SpellActionTake, ECS::SpellActionDrop, ECS::SpellActionThrow,
		ECS::SpellActionSwitch,
		ECS::SpellActionOpen, ECS::SpellActionClose,
		ECS::SpellActionUnlock, ECS::SpellActionLock,
		ECS::RenderLight>(spellSerial);

	spellSerial.SaveToFile("chrysalis/parameters/spells/spells_snapshot.xml");
}
}
