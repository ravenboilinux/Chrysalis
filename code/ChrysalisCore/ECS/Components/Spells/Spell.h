#pragma once

#include "ECS//Components/Components.h"


namespace Chrysalis::ECS
{
/**
	Requirements:

	targetType - enemy, ally, neutral?
	description - in simple text, no markdown?
	resistanceType - is this appropriate at a spell level?
	castTime - in seconds
	requireLoS
	add hate
	dot stacks
	max targets
	damage reduction for multiple targets

	*** use the meta to store a means of executing the spell components? maybe with their support for functions / properties / etc
	will we need to use a flag component to let us know which entities need this special processing? this would allow us to queue them
	up with the other spells e.g. damage and heals
	
	*** ISpellContainer - allows a component to contain a list of spells that can be cast when interacting with them. Players and NPCs
	would need spells for things like trading, inspecting, ... or maybe that should just be intrinsic - will need to flesh that
	out a little better.

*/




/** When spells are cast they require some changes from the prototype in order to function correctly.
	In order to get this right we need to know what changes it expects, and apply those as required.
	This should provide a high degree of flexibility, since we will be able to handle common spell
	types without knowlegde of their specifics. */

enum class SpellRewire
{
	none,				// Nothing special needs to be done.
	damage,				// Apply source, target, update damage values and qi use.
	heal,				// Apply source, target, update heal values and qi use.
	regenerate,			// ** Special case - mana regen on another
	crowdControl,		// Apply source, target - and whatever else...not sure yet.
	custom				// Need custom logic and handling to make this work.
};


enum class SpellCastStyle
{
	instant,			// Spell is cast instantly. Can't be interupted. Can be cast while moving.
	movementAllowed,	// A cast time applies - may be cast while moving.
	turret,				// A cast time applies. No movement allowed.
	channelled			// Continuous concentration requirement. No movement allowed.
};


struct Spell : public IComponent
{
	Spell() = default;
	virtual ~Spell() = default;


	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"spell"_hs};

		return nameHS;
	}


	bool Serialize(Serialization::IArchive& archive) override final
	{
		archive(spellRewire, "spell-rewire", "Actions which need to be taken before spell can be fired.");
		archive(minRange, "minRange", "Minimum range at which this can be cast.");
		archive(maxRange, "maxRange", "Maximum range at which this can be cast.");
		archive(castDuration, "castDuration", "The length of time it takes to cast this spell. Instant cast spells should be zero.");
		archive(cooldown, "cooldown", "Cooldown. The number of seconds before this spell can be cast again.");
		archive(globalCooldown, "globalCooldown", "Global cooldown. The number of seconds before *any* spell can be cast again.");

		return true;
	}

	/** Code that needs to run after a spell is copied to fix up all the broken requirements e.g. source, target, spell bonuses */
	SpellRewire spellRewire {SpellRewire::damage};

	/** Minimum range at which this can be cast. */
	float minRange {0.0f};

	/** Maximum range at which this can be cast. */
	float maxRange {30.0f};

	/** The length of time it takes to cast this spell. Instant cast spells should be zero. */
	float castDuration {2.0f};

	/** Cooldown. The number of seconds before this spell can be cast again. */
	float cooldown {2.0f};

	/** Global cooldown. The number of seconds before *any* spell can be cast again. */
	float globalCooldown {0.0f};
};
}