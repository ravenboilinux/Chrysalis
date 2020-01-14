#pragma once

#include <entt/entt.hpp>


namespace Chrysalis::ECS
{
class ECSSimulation
{
public:
	/** One time initialisation. */
	void Init();

	/** Update tick, called during every frame update. */
	void Update(const float deltaTime);

	/** Immediate simulation. Responsible for things that require immediate attention each frame. */
	void UpdateImmediate(const float deltaTime);

	/** Tick updates are responsible for handling DoTs, HoTs, and other components that can tick at intervals. */
	void UpdateTick(const float deltaTime);

	/** Temporary function for testing the simulation during development. */
	void LoadSimulationData();

	/** Temporary function for testing the simulation during development. */
	void SaveSimulationData();

	/** Get a reference to the registry for actors. */
	entt::registry* GetActorRegistry() { return &m_actorRegistry; }

	/** Get a reference to the spell registry, which keeps prototypes for all the spells. */
	entt::registry* GetSpellRegistry() { return &m_spellRegistry; }

	/** Get's a spell entity using it's name. This function is =SLOW= so use it carefully. */
	// TODO: Make this function not be slow and full of suck.
	entt::entity GetSpellByName(const char* spellName);

private:
	entt::registry m_actorRegistry;
	entt::registry m_spellRegistry;
};
}