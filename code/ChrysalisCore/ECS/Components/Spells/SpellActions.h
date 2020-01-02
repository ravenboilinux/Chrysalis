#pragma once

#include "ECS/Components/Components.h"


namespace Chrysalis::ECS
{
struct SpellActionOpenDoor : public IComponent
{
	SpellActionOpenDoor() = default;
	virtual ~SpellActionOpenDoor() = default;


	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"open-door"_hs};

		return nameHS;
	}


	bool Serialize(Serialization::IArchive& archive) override final
	{
		//archive(range, "range", "Maximum range at which this can be cast.");

		return true;
	}

	/** Maximum range at which this can be cast. */
	float range {20.0f};
};
}