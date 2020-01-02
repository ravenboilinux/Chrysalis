#pragma once

#include <entt/entt.hpp>


namespace Chrysalis
{
/** Implement this interface to allow an entity to be able to participant in the spell casting system. */

struct ISpellParticipant
{
	/**
	Gets the ECS entity identifier for this participant.

	\return entt::null if it fails, else the entity identifier.
	**/
	virtual const entt::entity GetECSEntity() const = 0;
};
}