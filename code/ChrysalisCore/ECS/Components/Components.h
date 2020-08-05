#pragma once

#include <entt/entt.hpp>

/** Thinking about making this a single include header for convenience. */

namespace Chrysalis::ECS
{
template<typename TYPE>
struct AttributeType
{
	AttributeType() = default;
	virtual ~AttributeType() = default;

	AttributeType(TYPE base, TYPE baseModifiers, TYPE modifiers) :
		base(base), baseModifiers(baseModifiers), modifiers(modifiers)
	{
	}


	void Serialize(Serialization::IArchive& ar)
	{
		ar(base, "base", "base");
		ar(baseModifiers, "baseModifiers", "baseModifiers");
		ar(modifiers, "modifiers", "modifiers");
	}

	/** Returns the current value for base, after it's modifiers have been applied. */
	const TYPE GetBaseAttribute() const
	{
		return base + baseModifiers;
	}


	/** Returns the current value for the attribute, after it's modifiers have been applied. */
	const TYPE GetAttribute() const
	{
		return base + modifiers;
	}

	/** Represents the attribute without any modifiers applied to it. */
	TYPE base {100.0f};

	/** This modifier makes changes to the base value, instead of the frame value. Typical use would be for a health / strength 
	buff that increases the base value of the attribute. */
	TYPE baseModifiers {0};

	/** Modifiers for this frame. Should be calculated each frame prior to calculating the current value. */
	TYPE modifiers {0};
};


struct Name
{
	Name() = default;
	virtual ~Name() = default;

	Name(string name, string displayName) :
		name(name), displayName(displayName)
	{
	}


	void Serialize(Serialization::IArchive& ar)
	{
		ar(name, "name", "The name of this entity. It should be unique.");
		ar(displayName, "displayName", "The display name for this entity.");
	}

	/** A unique name. */
	string name;

	/** A name which can be used in the UI. */
	string displayName;
};


/**	A way of marking an entity and saying that is it based on the components of a different entity. The prototype entity
	needs to have a matching name and must exist in a registry of the designer's choice.

*/

struct Prototype
{
	Prototype() = default;
	virtual ~Prototype() = default;

	Prototype(string name) :
		name(name)
	{
	}
	

	void Serialize(Serialization::IArchive& ar)
	{
		ar(name, "name", "Unique name of the prototype for this entity.");
	}

	/** A unique name. */
	string name;
};


struct SourceAndTarget
{
	SourceAndTarget() = default;
	virtual ~SourceAndTarget() = default;

	SourceAndTarget(entt::entity sourceEntity, entt::entity targetEntity,
		EntityId crySourceEntityId, EntityId cryTargetEntityId) :
		sourceEntity(sourceEntity), targetEntity(targetEntity), crySourceEntityId(crySourceEntityId), cryTargetEntityId(cryTargetEntityId)
	{
	}

	void Serialize(Serialization::IArchive& ar)
	{
		// This is really meant to be an ephemeral structure, so it shouldn't need to serialise, but I
		// am adding one just in case.
		ar(sourceEntity, "sourceEntity", "Source Entity");
		ar(targetEntity, "targetEntity", "Target Entity");
		ar(crySourceEntityId, "crySourceEntityId", "Cry Source Entity ID");
		ar(cryTargetEntityId, "cryTargetEntityId", "Cry Target Entity ID");
	}

	/** The source entity (EnTT). */
	entt::entity sourceEntity {entt::null};

	/** The target entity (EnTT).*/
	entt::entity targetEntity {entt::null};

	/** The source entity (CRYENGINE). */
	EntityId crySourceEntityId {INVALID_ENTITYID};

	/** The target entity (CRYENGINE). */
	EntityId cryTargetEntityId {INVALID_ENTITYID};
};


struct Requirement
{
	/**  */
	// Need some way to have a list of requirements e.g. level, class, profession, skill, race
};


// A weapon is also an item, and thus must always have an ItemClass component in it's entity.
struct WeaponClass
{
	/**  */
};


struct Mesh
{
	/** File path to a mesh. */
	string modelFilePath;

	/** File path to a material which should be applied to the mesh. Can be empty. */
	string materialFilePath;
};


struct LootTableReference
{
	/** A reference to the loot table which should be used when calculating loot. */
	string lootTableReference;
};


// Should there be one of these for each sort of lock type? Do we remove them once the lock is opened / broken?
struct LockedWithKey
{
	/**  */
	string key;
};


struct Key
{
	/**  */
	string key;
};


struct Ownership
{
	/**  */
	int owner;
};


void RegisterComponentsWithMeta();

}