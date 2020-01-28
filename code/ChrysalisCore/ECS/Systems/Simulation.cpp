#include <StdAfx.h>

#include "Simulation.h"
#include "Systems.h"
#include "ECS/Components/Components.h"
#include "ECS/Components/Health.h"
#include "ECS/Components/Inventory.h"
#include "ECS/Components/Items.h"
#include "ECS/Components/Qi.h"
#include "ECS/Components/Spells/Spell.h"
#include "ECS/Components/Spells/SpellActions.h"
#include "ECS/Systems/Systems.h"
#include "ECS/Systems/XMLSerializer.h"
#include <entt/entt.hpp>
#include "Crymath/Random.h"


namespace Chrysalis::ECS
{
/** Takes a reference to a spell and applies the needed fixups. This is mainly going to fix up the source and targets
	for now. */
void CSimulation::RewireSpell(entt::registry& registry, entt::entity spellEntity, entt::entity sourceEntity, entt::entity targetEntity)
{
	ECS::Spell& spell = registry.get<ECS::Spell>(spellEntity);

	entt::entity source;
	entt::entity target;

	// The source should almost always be the real source of the spell.
	if (spell.sourceTargetType != ECS::TargetType::none)
	{
		source = sourceEntity;
	}
	else
	{
		source = entt::null;
	}

	switch (spell.targetTargetType)
	{
		// Targetting the caster.
		case ECS::TargetType::self:
			target = sourceEntity;
			break;

			// Not targetted at an entity.
		case ECS::TargetType::none:
		case ECS::TargetType::cone:
		case ECS::TargetType::column:
		case ECS::TargetType::sourceBasedAOE:
		case ECS::TargetType::groundTargettedAOE:
			target = entt::null;
			break;

			// Targetting the selected entity.
		default:
			target = targetEntity;
			break;
	}

	// The source and target for the spell need to be added to the entity.
	registry.assign<ECS::SourceAndTarget>(spellEntity, source, target);

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
void CSimulation::CastSpellByName(const char* spellName, entt::entity sourceEntity, entt::entity targetEntity)
{
	auto spellEntity = GetSpellByName(spellName);
	if (spellEntity != entt::null)
	{
		// Make use of the create feature to copy the spell prototype into the actor registry.
		auto newEntity = m_actorRegistry.create<ECS::Name, ECS::Health, ECS::Damage, ECS::DamageOverTime, ECS::Heal, ECS::HealOverTime,
			ECS::Qi, ECS::UtiliseQi, ECS::UtiliseQiOverTime, ECS::ReplenishQi, ECS::ReplenishQiOverTime,
			ECS::Spell,
			ECS::SpellActionSchematyc, ECS::SpellActionDRS,
			ECS::SpellActionInspect, ECS::SpellActionExamine,
			ECS::SpellActionTake, ECS::SpellActionDrop, ECS::SpellActionThrow,
			ECS::SpellActionSwitch,
			ECS::SpellActionOpen, ECS::SpellActionClose,
			ECS::SpellActionUnlock, ECS::SpellActionLock>(spellEntity, m_spellRegistry);

		// Do fixups.
		RewireSpell(m_actorRegistry, newEntity, sourceEntity, targetEntity);
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
	m_actorRegistry.snapshot()
		.entities(actorSerial)
		.component<ECS::Name,
		ECS::Health, ECS::Damage, ECS::DamageOverTime, ECS::Heal, ECS::HealOverTime,
		ECS::Qi, ECS::UtiliseQi, ECS::UtiliseQiOverTime, ECS::ReplenishQi, ECS::ReplenishQiOverTime,
		ECS::Spell,
		ECS::ItemClass>(actorSerial);
	actorSerial.SaveToFile("chrysalis/parameters/items/test-out-snapshot.xml");

	// Spell prototypes.
	ECS::SerialiseECS spellSerial;
	m_spellRegistry.snapshot()
		.entities(spellSerial)
		.component<ECS::Name,
		ECS::Health, ECS::Damage, ECS::DamageOverTime, ECS::Heal, ECS::HealOverTime,
		ECS::Qi, ECS::UtiliseQi, ECS::UtiliseQiOverTime, ECS::ReplenishQi, ECS::ReplenishQiOverTime,
		ECS::Spell,
		ECS::SpellActionSchematyc, ECS::SpellActionDRS,
		ECS::SpellActionInspect, ECS::SpellActionExamine,
		ECS::SpellActionTake, ECS::SpellActionDrop, ECS::SpellActionThrow,
		ECS::SpellActionSwitch,
		ECS::SpellActionOpen, ECS::SpellActionClose, 
		ECS::SpellActionUnlock, ECS::SpellActionLock>(spellSerial);

	spellSerial.SaveToFile("chrysalis/parameters/spells/spells-snapshot.xml");
}
}
