#pragma once

#include <entt/entt.hpp>

/** Thinking about making this a single include header for convenience. */

namespace Chrysalis::ECS
{
struct IComponent
{
	IComponent() = default;
	virtual ~IComponent() = default;

	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"icomponent"_hs};

		return nameHS;
	}

	// This should be pure virtual but the ECS needs to be able to instantiate the struct, so...here's nothing.
	virtual bool Serialize(Serialization::IArchive& archive) { return true; };
};


template<typename TYPE>
struct AttributeType
{
	AttributeType() = default;
	virtual ~AttributeType() = default;

	AttributeType(TYPE base, TYPE baseModifiers, TYPE modifiers) :
		base(base), baseModifiers(baseModifiers), modifiers(modifiers)
	{
	}


	bool Serialize(Serialization::IArchive& archive)
	{
		archive(base, "base", "base");
		archive(baseModifiers, "baseModifiers", "baseModifiers");
		archive(modifiers, "modifiers", "modifiers");

		return true;
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


struct Name : public IComponent
{
	Name() = default;
	virtual ~Name() = default;

	Name(string name, string displayName) :
		name(name), displayName(displayName)
	{
	}
	

	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"name"_hs};

		return nameHS;
	}


	bool Serialize(Serialization::IArchive& archive) override final
	{
		archive(name, "name", "name");
		archive(displayName, "displayName", "displayName");

		return true;
	}

	/** A unique name for this particular item class. */
	string name;

	/** A name which can be used in the UI. */
	string displayName;
};


struct SourceAndTarget : public IComponent
{
	SourceAndTarget() = default;
	virtual ~SourceAndTarget() = default;

	SourceAndTarget(entt::entity sourceEntity, entt::entity targetEntity,
		EntityId crySourceEntityId, EntityId cryTargetEntityId) :
		sourceEntity(sourceEntity), targetEntity(targetEntity), crySourceEntityId(crySourceEntityId), cryTargetEntityId(cryTargetEntityId)
	{
	}

	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"source-and-target"_hs};

		return nameHS;
	}


	bool Serialize(Serialization::IArchive& archive) override final
	{
		// This is really meant to be an ephemeral structure, so it shouldn't need to serialise, but I
		// am adding one just in case.
		archive(sourceEntity, "sourceEntity", "Source Entity");
		archive(targetEntity, "targetEntity", "Target Entity");
		archive(crySourceEntityId, "crySourceEntityId", "Cry Source Entity ID");
		archive(cryTargetEntityId, "cryTargetEntityId", "Cry Target Entity ID");

		return true;
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