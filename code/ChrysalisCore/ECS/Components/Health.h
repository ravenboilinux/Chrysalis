#pragma once

#include <ECS/Components/Spells/Spell.h>


namespace Chrysalis::ECS
{
enum class DamageType
{
	acid,
	bleed,
	cold,
	collision,
	cleave,
	crush,
	decay,
	disease,
	electricity,
	energy,
	entropy,
	explosion,
	fire,
	holy,
	ice,
	nature,
	pierce,
	plasma,
	poison,
	qi,
	radiation,
	slash,
	tear,
	unholy
};


struct Health : public IComponent
{
	Health() = default;
	virtual ~Health() = default;

	Health(AttributeType<float> health) :
		health(health)
	{
	}


	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"health"_hs};

		return nameHS;
	}


	bool Serialize(Serialization::IArchive& archive) override final
	{
		archive(health, "health", "health");

		return true;
	}

	/** Health attribute. */
	AttributeType<float> health;

	/** Is the actor dead? */
	bool isDead {false};
};


struct Damage : public IComponent
{
	Damage() = default;
	virtual ~Damage() = default;

	Damage(float quantity, DamageType damageType) :
		quantity(quantity), damageType(damageType)
	{
	}


	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"damage"_hs};

		return nameHS;
	}


	bool Serialize(Serialization::IArchive& archive) override final
	{
		archive(targetTargetType, "targetTargetType", "targetTargetType");
		archive(quantity, "quantity", "quantity");
		archive(damageType, "damageType", "Damage Type");

		return true;
	}

	/** Use the spell's target or source for this component's target. */
	TargetTargetType targetTargetType {TargetTargetType::target};

	/** Modify an attribute by this amount. */
	float quantity {0.0f};

	/** The type of damage. */
	DamageType damageType {DamageType::acid};
};


struct DamageOverTime : public IComponent
{
	DamageOverTime() = default;
	virtual ~DamageOverTime() = default;

	DamageOverTime(float quantity, DamageType damageType,
		float duration, float interval) :
		quantity(quantity), damageType(damageType),
		duration(duration), interval(interval)
	{
		ticksRemaining = duration / interval;
	}


	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"damage-over-time"_hs};

		return nameHS;
	}


	bool Serialize(Serialization::IArchive& archive) override final
	{
		archive(targetTargetType, "targetTargetType", "targetTargetType");
		archive(quantity, "quantity", "quantity");
		archive(damageType, "damageType", "damageType");
		archive(duration, "duration", "duration");
		archive(interval, "interval", "interval");

		return true;
	}

	/** Use the spell's target or source for this component's target. */
	TargetTargetType targetTargetType {TargetTargetType::target};

	/** Modify an attribute by this amount. */
	float quantity {0.0f};

	/** The type of damage. */
	DamageType damageType {DamageType::acid};

	/** Limit the duration for this modifier. Given as remaining time in seconds. */
	float duration {10.0f};

	/** The ticks need to occur at this interval. */
	float interval {1.0f};

	/** Gametime passed since the last tick. */
	float deltaSinceTick {0.0f};

	/** Ticks remaining. */
	float ticksRemaining {duration / interval};
};


struct Heal : public IComponent
{
	Heal() = default;
	virtual ~Heal() = default;

	Heal(float quantity) :
		quantity(quantity)
	{
	}


	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"heal"_hs};

		return nameHS;
	}


	bool Serialize(Serialization::IArchive& archive) override final
	{
		archive(targetTargetType, "targetTargetType", "targetTargetType");
		archive(quantity, "quantity", "quantity");

		return true;
	}

	/** Use the spell's target or source for this component's target. */
	TargetTargetType targetTargetType {TargetTargetType::target};

	/** Modify an attribute by this amount. */
	float quantity {0.0f};
};


struct HealOverTime : public IComponent
{
	HealOverTime() = default;
	virtual ~HealOverTime() = default;

	HealOverTime(float quantity,
		float duration, float interval) :
		quantity(quantity), duration(duration), interval(interval)
	{
	}


	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"heal-over-time"_hs};

		return nameHS;
	}


	bool Serialize(Serialization::IArchive& archive) override final
	{
		archive(targetTargetType, "targetTargetType", "targetTargetType");
		archive(quantity, "quantity", "quantity");
		archive(duration, "duration", "duration");
		archive(interval, "interval", "interval");

		return true;
	}

	/** Use the spell's target or source for this component's target. */
	TargetTargetType targetTargetType {TargetTargetType::target};

	/** Modify an attribute by this amount. */
	float quantity {0.0f};

	/** Limit the duration for this modifier. Given as remaining time in seconds. */
	float duration {10.0f};

	/** The ticks need to occur at this interval. */
	float interval {1.0f};

	/** Gametime passed since the last tick. */
	float deltaSinceTick {0.0f};

	/** Ticks remaining. */
	float ticksRemaining {duration / interval};
};
}