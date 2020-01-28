#include <StdAfx.h>

#include "Systems.h"
#include "ECS/Components/Health.h"
#include "ECS/Components/Inventory.h"
#include "ECS/Components/Items.h"
#include "ECS/Components/Qi.h"


namespace Chrysalis::ECS
{
// ***
// *** Health System
// ***


void SystemApplyDamage(entt::registry& registry)
{
	// Apply any damage to the damage modifiers.
	auto view = registry.view<ECS::Damage, ECS::SourceAndTarget>();
	for (auto& entity : view)
	{
		// Get the components.
		auto& damage = view.get<ECS::Damage>(entity);
		auto& sourceAndTarget = view.get<ECS::SourceAndTarget>(entity);

		// Get the health component for the target entity and apply the damage to it's health modifier.
		ECS::Health* targetHealth {nullptr};
		if (damage.targetTargetType == TargetTargetType::target)
		{
			auto& health = registry.get<ECS::Health>(sourceAndTarget.targetEntity);
			targetHealth = &health;
		}
		else
		{
			auto& health = registry.get<ECS::Health>(sourceAndTarget.sourceEntity);
			targetHealth = &health;
		}

		targetHealth->health.modifiers -= damage.quantity;

		// Remove just the component.
		registry.remove<ECS::Damage>(entity);
	}
}


void SystemApplyDamageOverTime(float dt, entt::registry& registry)
{
	// Apply any damage to the damage modifiers.
	auto view = registry.view<ECS::DamageOverTime, ECS::SourceAndTarget>();
	for (auto& entity : view)
	{
		// Get the components..
		auto& damage = view.get<ECS::DamageOverTime>(entity);
		auto& sourceAndTarget = view.get<ECS::SourceAndTarget>(entity);

		damage.deltaSinceTick += dt;
		if ((damage.deltaSinceTick >= damage.interval) && (damage.ticksRemaining >= 1.0f))
		{
			damage.ticksRemaining--;
			damage.deltaSinceTick -= damage.interval;

			// Get the health component for the target entity and apply the damage to it's health modifier.
			ECS::Health* targetHealth {nullptr};
			if (damage.targetTargetType == TargetTargetType::target)
			{
				auto& health = registry.get<ECS::Health>(sourceAndTarget.targetEntity);
				targetHealth = &health;
			}
			else
			{
				auto& health = registry.get<ECS::Health>(sourceAndTarget.sourceEntity);
				targetHealth = &health;
			}
			targetHealth->health.modifiers -= damage.quantity;
		}

		if (damage.ticksRemaining <= 0.0f)
		{
			// Remove just the component.
			registry.remove<ECS::DamageOverTime>(entity);
		}
	}
}


void SystemApplyHeal(entt::registry& registry)
{
	// Apply any heals to the health modifiers.
	auto view = registry.view<ECS::Heal, ECS::SourceAndTarget>();
	for (auto& entity : view)
	{
		// Get the components..
		auto& heal = view.get<ECS::Heal>(entity);
		auto& sourceAndTarget = view.get<ECS::SourceAndTarget>(entity);

		// Get the health component for the target entity and apply the heal to it's health modifier.
		ECS::Health* targetHealth {nullptr};
		if (heal.targetTargetType == TargetTargetType::target)
		{
			auto& health = registry.get<ECS::Health>(sourceAndTarget.targetEntity);
			targetHealth = &health;
		}
		else
		{
			auto& health = registry.get<ECS::Health>(sourceAndTarget.sourceEntity);
			targetHealth = &health;
		}

		// Check for overheals.
		float newModifier = targetHealth->health.modifiers + heal.quantity;
		if (newModifier > 0.0f)
		{
			// It was an overheal.
			targetHealth->health.modifiers = 0.0f;
		}
		else
		{
			targetHealth->health.modifiers = newModifier;
		}

		// Remove just the component.
		registry.remove<ECS::Heal>(entity);
	}
}


void SystemApplyHealOverTime(float dt, entt::registry& registry)
{
	// Apply any heal to the health modifiers.
	auto view = registry.view<ECS::HealOverTime, ECS::SourceAndTarget>();
	for (auto& entity : view)
	{
		// Get the components..
		auto& heal = view.get<ECS::HealOverTime>(entity);
		auto& sourceAndTarget = view.get<ECS::SourceAndTarget>(entity);

		heal.deltaSinceTick += dt;
		if ((heal.deltaSinceTick >= heal.interval) && (heal.ticksRemaining >= 1.0f))
		{
			heal.ticksRemaining--;
			heal.deltaSinceTick -= heal.interval;

			// Get the health component for the target entity and apply the heal to it's health modifier.
			ECS::Health* targetHealth {nullptr};
			if (heal.targetTargetType == TargetTargetType::target)
			{
				auto& health = registry.get<ECS::Health>(sourceAndTarget.targetEntity);
				targetHealth = &health;
			}
			else
			{
				auto& health = registry.get<ECS::Health>(sourceAndTarget.sourceEntity);
				targetHealth = &health;
			}


			// Check for overheals.
			float newModifier = targetHealth->health.modifiers + heal.quantity;
			if (newModifier > 0.0f)
			{
				// It was an overheal.
				targetHealth->health.modifiers = 0.0f;
			}
			else
			{
				targetHealth->health.modifiers = newModifier;
			}

			if (heal.ticksRemaining <= 0.0f)
			{
				// Remove just the component.
				registry.remove<ECS::HealOverTime>(entity);
			}
		}
	}
}


void SystemHealthCheck(entt::registry& registry)
{
	// Update each health component, applying the modifier to it's base to calculate the current health.
	// Update death status if appropriate.
	auto view = registry.view<ECS::Health, ECS::SourceAndTarget>();
	for (auto& entity : view)
	{
		// Get the components..
		auto& health = view.get<ECS::Health>(entity);

		// Check for overkill.
		float newHealth = health.health.GetBaseAttribute() + health.health.modifiers;
		if (newHealth <= 0.0f)
		{
			health.isDead = true;

			// TODO: Inform them they died with -newHealth being the amount of overkill.
		}
	}
}


// ***
// *** Qi System
// ***


void SystemApplyQiUtilisation(entt::registry& registry)
{
	// Apply any qi usage to the modifiers.
	auto view = registry.view<ECS::UtiliseQi, ECS::SourceAndTarget>();
	for (auto& entity : view)
	{
		// Get the components..
		auto& qiUse = view.get<ECS::UtiliseQi>(entity);
		auto& sourceAndTarget = view.get<ECS::SourceAndTarget>(entity);
		
		// Get the qi component for the target entity and apply the usage to it's modifier.
		ECS::Qi* targetQi {nullptr};
		if (qiUse.targetTargetType == TargetTargetType::target)
		{
			auto& qi = registry.get<ECS::Qi>(sourceAndTarget.targetEntity);
			targetQi = &qi;
		}
		else
		{
			auto& qi = registry.get<ECS::Qi>(sourceAndTarget.sourceEntity);
			targetQi = &qi;
		}

		// Get the qi component for the target entity and apply the usage to it's modifier.
		targetQi->qi.modifiers -= qiUse.quantity;

		// Remove just the component.
		registry.remove<ECS::UtiliseQi>(entity);
	}
}


void SystemApplyQiUtilisationOverTime(float dt, entt::registry& registry)
{
	// Apply any qi to the modifiers.
	auto view = registry.view<ECS::UtiliseQiOverTime, ECS::SourceAndTarget>();
	for (auto& entity : view)
	{
		// Get the components..
		auto& qiUse = view.get<ECS::UtiliseQiOverTime>(entity);
		auto& sourceAndTarget = view.get<ECS::SourceAndTarget>(entity);

		qiUse.deltaSinceTick += dt;
		if ((qiUse.deltaSinceTick >= qiUse.interval) && (qiUse.ticksRemaining >= 1.0f))
		{
			qiUse.ticksRemaining--;
			qiUse.deltaSinceTick -= qiUse.interval;

			// Get the qi component for the target entity and apply the usage to it's modifier.
			ECS::Qi* targetQi {nullptr};
			if (qiUse.targetTargetType == TargetTargetType::target)
			{
				auto& qi = registry.get<ECS::Qi>(sourceAndTarget.targetEntity);
				targetQi = &qi;
			}
			else
			{
				auto& qi = registry.get<ECS::Qi>(sourceAndTarget.sourceEntity);
				targetQi = &qi;
			}
			targetQi->qi.modifiers -= qiUse.quantity;
		}

		if (qiUse.ticksRemaining <= 0.0f)
		{
			// Remove just the component.
			registry.remove<ECS::UtiliseQiOverTime>(entity);
		}
	}
}


void SystemApplyQiReplenishment(entt::registry& registry)
{
	// Apply any replenishment to the qi modifiers.
	auto view = registry.view<ECS::ReplenishQi, ECS::SourceAndTarget>();
	for (auto& entity : view)
	{
		// Get the components..
		auto& replenish = view.get<ECS::ReplenishQi>(entity);
		auto& sourceAndTarget = view.get<ECS::SourceAndTarget>(entity);

		// Get the qi component for the target entity and apply the replenishment to it's modifier.
		ECS::Qi* targetQi {nullptr};
		if (replenish.targetTargetType == TargetTargetType::target)
		{
			auto& qi = registry.get<ECS::Qi>(sourceAndTarget.targetEntity);
			targetQi = &qi;
		}
		else
		{
			auto& qi = registry.get<ECS::Qi>(sourceAndTarget.sourceEntity);
			targetQi = &qi;
		}

		// Check for over-replenishment.
		float newModifier = targetQi->qi.modifiers + replenish.quantity;
		if (newModifier > 0.0f)
		{
			// It was an over-replenishment.
			targetQi->qi.modifiers = 0.0f;
		}
		else
		{
			targetQi->qi.modifiers = newModifier;
		}

		// Remove just the component.
		registry.remove<ECS::ReplenishQi>(entity);
	}
}


void SystemApplyQiReplenishmentOverTime(float dt, entt::registry& registry)
{
	// Apply any replenishment to the qi modifiers.
	auto view = registry.view<ECS::ReplenishQiOverTime, ECS::SourceAndTarget>();
	for (auto& entity : view)
	{
		// Get the components..
		auto& replenish = view.get<ECS::ReplenishQiOverTime>(entity);
		auto& sourceAndTarget = view.get<ECS::SourceAndTarget>(entity);

		replenish.deltaSinceTick += dt;
		if ((replenish.deltaSinceTick >= replenish.interval) && (replenish.ticksRemaining >= 1.0f))
		{
			replenish.ticksRemaining--;
			replenish.deltaSinceTick -= replenish.interval;

			// Get the qi component for the target entity and apply the replenishment to it's modifier.
			ECS::Qi* targetQi {nullptr};
			if (replenish.targetTargetType == TargetTargetType::target)
			{
				auto& qi = registry.get<ECS::Qi>(sourceAndTarget.targetEntity);
				targetQi = &qi;
			}
			else
			{
				auto& qi = registry.get<ECS::Qi>(sourceAndTarget.sourceEntity);
				targetQi = &qi;
			}

			// Check for over-replenishment.
			float newModifier = targetQi->qi.modifiers + replenish.quantity;
			if (newModifier > 0.0f)
			{
				// It was an over-replenishment.
				targetQi->qi.modifiers = 0.0f;
			}
			else
			{
				targetQi->qi.modifiers = newModifier;
			}

			if (replenish.ticksRemaining <= 0.0f)
			{
				// Remove just the component.
				registry.remove<ECS::ReplenishQiOverTime>(entity);
			}
		}
	}
}


// ***
// *** World Spellcasts
// ***


bool IsSpellCastable(const ECS::Spell& spell, const ECS::SourceAndTarget& sourceAndTarget)
{
	// TODO: Range and LoS checks, etc.

	return true;
}


void SpellCastTake(float dt, entt::registry& registry)
{
	// Check for spell cast components.
	auto view = registry.view<ECS::SpellActionTake, ECS::Name, ECS::Spell, ECS::SourceAndTarget>();
	for (auto& entity : view)
	{
		// Get the components.
		auto& name = view.get<ECS::Name>(entity);
		auto& spell = view.get<ECS::Spell>(entity);
		auto& sourceAndTarget = view.get<ECS::SourceAndTarget>(entity);

		// Check validity of the spell cast request.
		if (IsSpellCastable(spell, sourceAndTarget))
		{
			// Do something.
			CryLogAlways("Spellcast: %s, Source: %d, target: %d", name.displayName.c_str(), sourceAndTarget.sourceEntity, sourceAndTarget.targetEntity);
		}

		// Destroy the entity. Assumption is each entity only has one of these sorts of spell components on it. 
		registry.destroy(entity);
	}
}


void SpellCastDrop(float dt, entt::registry& registry)
{
	// Check for spell cast components.
	auto view = registry.view<ECS::SpellActionDrop, ECS::Name, ECS::Spell, ECS::SourceAndTarget>();
	for (auto& entity : view)
	{
		// Get the components.
		auto& name = view.get<ECS::Name>(entity);
		auto& spell = view.get<ECS::Spell>(entity);
		auto& sourceAndTarget = view.get<ECS::SourceAndTarget>(entity);

		// Check validity of the spell cast request.
		if (IsSpellCastable(spell, sourceAndTarget))
		{
			// Do something.
			CryLogAlways("Spellcast: %s, Source: %d, target: %d", name.displayName.c_str(), sourceAndTarget.sourceEntity, sourceAndTarget.targetEntity);
		}

		// Destroy the entity. Assumption is each entity only has one of these sorts of spell components on it. 
		registry.destroy(entity);
	}
}


void SpellCastSwitch(float dt, entt::registry& registry)
{
	// Check for spell cast components.
	auto view = registry.view<ECS::SpellActionSwitch, ECS::Name, ECS::Spell, ECS::SourceAndTarget>();
	for (auto& entity : view)
	{
		// Get the components.
		auto& name = view.get<ECS::Name>(entity);
		auto& spell = view.get<ECS::Spell>(entity);
		auto& sourceAndTarget = view.get<ECS::SourceAndTarget>(entity);

		// Check validity of the spell cast request.
		if (IsSpellCastable(spell, sourceAndTarget))
		{
			// Do something.
			CryLogAlways("Spellcast: %s, Source: %d, target: %d", name.displayName.c_str(), sourceAndTarget.sourceEntity, sourceAndTarget.targetEntity);
		}

		// Destroy the entity. Assumption is each entity only has one of these sorts of spell components on it. 
		registry.destroy(entity);
	}
}


void SystemWorldSpellCasts(float dt, entt::registry& registry)
{
	SpellCastTake(dt, registry);
	SpellCastDrop(dt, registry);
	SpellCastSwitch(dt, registry);
}
}
