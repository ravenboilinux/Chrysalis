#pragma once

#include <entt/entt.hpp>


namespace Chrysalis::ECS
{
class CSimulation
{
public:
	/** One time initialisation. */
	void Init();

	/** Update tick, called during every frame update. */
	void Update(const float deltaTime);

	/** Immediate Simulation. Responsible for things that require immediate attention each frame. */
	void UpdateImmediate(const float deltaTime);

	/** Tick updates are responsible for handling DoTs, HoTs, and other components that can tick at intervals. */
	void UpdateTick(const float deltaTime);

	/** World spellcasts are the various commands for interacting with the world. */
	void UpdateWorldSpellcasts(const float deltaTime);

	/** Temporary function for testing the Simulation during development. */
	void LoadSimulationData();

	/** Temporary function for testing the Simulation during development. */
	void SaveSimulationData();

	/** Get a reference to the registry for actors. */
	entt::registry* GetActorRegistry() { return &m_actorRegistry; }

	/** Get a reference to the spell registry, which keeps prototypes for all the spells. */
	entt::registry* GetSpellRegistry() { return &m_spellRegistry; }

	/** Performs some important fixups to the spell entity, based on the type of spell. Source and target entities
	are rewired to work as expected. */
	void RewireSpell(entt::registry& registry, entt::entity spellEntity, entt::entity sourceEntity, entt::entity targetEntity);
		
	// TODO: Make this function not be slow and full of suck.
	/** Get's a spell entity using it's name. This function is =SLOW= so use it carefully. */
	entt::entity GetSpellByName(const char* spellName);

	/** Casts a spell, using the spell name as an index into the spell registry. */
	void CastSpellByName(const char* spellName, entt::entity sourceEntity, entt::entity targetEntity);

private:
	entt::registry m_actorRegistry;
	entt::registry m_spellRegistry;
};
}