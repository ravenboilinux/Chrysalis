#pragma once

#include "Components.h"


namespace Chrysalis::ECS
{
struct Qi : public IComponent
{
	Qi() = default;
	virtual ~Qi() = default;

	Qi(AttributeType<float> qi) :
		qi(qi)
	{
	}


	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"qi"_hs};

		return nameHS;
	}


	bool Serialize(Serialization::IArchive& archive) override final
	{
		archive(qi, "qi", "qi");

		return true;
	}

	/** Qi attribute. */
	AttributeType<float> qi;
};


struct UtiliseQi : public IComponent
{
	UtiliseQi() = default;
	virtual ~UtiliseQi() = default;

	UtiliseQi(float quantity) :
		quantity(quantity)
	{
	}


	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"utilise-qi"_hs};

		return nameHS;
	}


	bool Serialize(Serialization::IArchive& archive) override final
	{
		archive(quantity, "quantity", "quantity");

		return true;
	}

	/** Modify an attribute by this amount. */
	float quantity {0.0f};
};


struct UtiliseQiOverTime : public IComponent
{
	UtiliseQiOverTime() = default;
	virtual ~UtiliseQiOverTime() = default;

	UtiliseQiOverTime(float quantity,
		float duration, float interval) :
		quantity(quantity), duration(duration), interval(interval)
	{
	}


	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"utilise-qi-over-time"_hs};

		return nameHS;
	}


	bool Serialize(Serialization::IArchive& archive) override final
	{
		archive(quantity, "quantity", "quantity");
		archive(duration, "duration", "duration");
		archive(interval, "interval", "interval");

		return true;
	}

	/** Modify an attribute by this amount. */
	float quantity {0.0f};

	/** Limit the duration for this modifier. Given as remaining time in seconds. */
	float duration {10.0f};

	/** The damage ticks need to occur at this interval. */
	float interval {1.0f};

	/** Gametime passed since the last tick. */
	float deltaSinceTick {0.0f};

	/** Ticks remaining. */
	float ticksRemaining {duration / interval};
};


struct ReplenishQi : public IComponent
{
	ReplenishQi() = default;
	virtual ~ReplenishQi() = default;

	ReplenishQi(float quantity) :
		quantity(quantity)
	{
	}


	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"replenish-qi"_hs};

		return nameHS;
	}


	bool Serialize(Serialization::IArchive& archive) override final
	{
		archive(quantity, "quantity", "quantity");

		return true;
	}

	/** Modify an attribute by this amount. */
	float quantity {0.0f};
};


struct ReplenishQiOverTime : public IComponent
{
	ReplenishQiOverTime() = default;
	virtual ~ReplenishQiOverTime() = default;

	ReplenishQiOverTime(float quantity,
		float duration, float interval) :
		quantity(quantity), duration(duration), interval(interval)
	{
	}


	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"replenish-qi-over-time"_hs};

		return nameHS;
	}


	bool Serialize(Serialization::IArchive& archive) override final
	{
		archive(quantity, "quantity", "quantity");
		archive(duration, "duration", "duration");
		archive(interval, "interval", "interval");

		return true;
	}

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