#pragma once

#include <Entities/Interaction/IEntityInteraction.h>
#include <ECS/Components/Spells/Spell.h>
#include <entt/entt.hpp>


namespace Chrysalis
{
/** React to events in the lifetime of a spell cast. */

struct ISpellCasting
{
	/**
	Called at the start of a spell cast. Generally called on a downward keypress.
	**/

	virtual void OnSpellStart() = 0;

	/**
	Called each game frame a spell is stil casting. This will be called multiple times, as long as the player is
	holding down the key / button.
	**/

	virtual void OnSpellTick() = 0;

	/**
	Called when a spellcast is interupted by something. Spell casting can continue, but with some penalty applied.
	**/
	virtual void OnSpellInterupt() = 0;

	/**
	Called when an spellcast fails or fizzles e.g. target out of range during channelling.
	**/

	virtual void OnSpellFail() = 0;

	/**
	Called when an interaction is completed normally. Generally called on an upward keypress.
	**/

	virtual void OnSpellComplete() = 0;
};


/** Interface to allow queueing a spell for execution. */
struct ISpellCastManager
{
	/** Queue a spell up, ready for casting. */
	virtual bool QueueSpellCast(std::shared_ptr<ISpellCasting> spellCasting) = 0;
};


struct SpellCastOpen : public ISpellCasting
{

	SpellCastOpen(ECS::Name name, ECS::Spell spell, ECS::SourceAndTarget sourceAndTarget)
		:name(name), spell(spell), sourceAndTarget(sourceAndTarget) {}
	~SpellCastOpen() = default;

	// ISpellCasting
	virtual void OnSpellStart() { CryLogAlways("Spell cast open: start"); }
	virtual void OnSpellTick() { /*CryLogAlways("Spell cast open: tick");*/ }
	virtual void OnSpellInterupt() { CryLogAlways("Spell cast open: interupt"); }
	virtual void OnSpellFail() { CryLogAlways("Spell cast open: fail"); }
	virtual void OnSpellComplete() { CryLogAlways("Spell cast open: complete"); }
	// ~ISpellCasting

	ECS::Name name;
	ECS::Spell spell;
	ECS::SourceAndTarget sourceAndTarget;
};


/**
Allows an entity to have a spellbook which can hold spells both castable by the entity, as well as from outside
sources if desired.

\sa IEntityComponent
**/

class CSpellbookComponent
	: public IEntityComponent, public ISpellCastManager
{
protected:
	// IEntityComponent
	void Initialize() override;
	// ~IEntityComponent

public:
	CSpellbookComponent() {}
	virtual ~CSpellbookComponent() {}

	static void ReflectType(Schematyc::CTypeDesc<CSpellbookComponent>& desc);

	static CryGUID& IID()
	{
		static CryGUID id = "{654A1648-663E-414B-97C1-0A7B12D3072F}"_cry_guid;
		return id;
	}


	// ISpellCastManager
	bool QueueSpellCast(std::shared_ptr<ISpellCasting> spellCasting) override;
	// ~ISpellCastManager


	/** An entry in the spellbook. This should name the spell, and provide meta information on casting
	limitations that exist in addition to the limitations of the spell itself. */
	struct SSpellBookEntry
	{
		void Serialize(Serialization::IArchive& ar)
		{
			ar(spellName, "spellName", "Name");
			ar(isHidden, "isHidden", "Hidden?");
			ar(enabled, "enabled", "Enabled?");
		}

		/** The name of the spell must be found inside the spell registry in order for the spell to work correctly. */
		string spellName;

		/** The prototype for this spell. These will need to be looked up each time the spell name changes or
		whenever an entry is loaded. Attempts to use the spell should check for null spells which indicate
		some form of error has occurred or the spell prototype doesn't exist. */
		entt::entity prototype {entt::null};

		/** Provide a means of disabling spells. */
		bool isHidden {false};

		/** Provide a means of disabling spells. */
		bool enabled {true};
	};


	/*** A collection of spell entries. This is the soul of a spellbook. Every spell that can be cast
	should be found in this collection. */
	struct SSpellCollection
	{
		inline bool operator==(const SSpellCollection& rhs) const { return 0 == memcmp(this, &rhs, sizeof(rhs)); }

		static void ReflectType(Schematyc::CTypeDesc<SSpellCollection>& desc)
		{
			desc.SetGUID("{CF8E39CE-CC1E-4E05-9536-B1403723CC5B}"_cry_guid);
		}


		void Serialize(Serialization::IArchive& ar)
		{
			ar(spells, "spells", "spells");
		}

		std::vector<SSpellBookEntry> spells;
	};


	std::vector<string> GetVerbs(bool includeHidden = false);

	void AddInteraction(IInteractionPtr interaction);
	void RemoveInteraction(string verb);
	IInteractionWeakPtr GetInteraction(string verb);
	IInteractionWeakPtr SelectInteractionVerb(string verb);
	void ClearInteractionVerb();

	void OnInteractionStart(IActor& actor);
	void OnInteractionTick(IActor& actor);
	void OnInteractionComplete(IActor& actor);

	const SSpellCollection& GetSpellColllection() const { return m_spellCollection; }

private:
	/** A collection of spells which can potentially be cast. */
	SSpellCollection m_spellCollection;

	// Older interaction system - looking at spell casting now instead.
	std::vector<IInteractionPtr> m_interactionQueue;
	IInteractionPtr m_selectedInteraction {IInteractionPtr()};

	// HACK: KISS - no queue for the moment.
	std::queue<std::shared_ptr<ISpellCasting>> m_spellQueue;
	std::shared_ptr<ISpellCasting> m_spellCasting;
};
}