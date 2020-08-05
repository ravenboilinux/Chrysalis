#pragma once

#include "ECS/Components/Components.h"


namespace Chrysalis::ECS
{
/** Raise a schematyc event. */
struct SpellActionSchematyc
{
	SpellActionSchematyc() = default;
	virtual ~SpellActionSchematyc() = default;


	void Serialize(Serialization::IArchive& archive) { ; }
};


/** Raise a DRS event. */
struct SpellActionDRS
{
	SpellActionDRS() = default;
	virtual ~SpellActionDRS() = default;


	void Serialize(Serialization::IArchive& archive) { ; }
};


/** Take a closer look at some environmental feature e.g. a time clock for punching into work. */
struct SpellActionInspect
{
	SpellActionInspect() = default;
	virtual ~SpellActionInspect() = default;


	void Serialize(Serialization::IArchive& archive) { ; }
};


/** Examine an item while holding it in your hands. You should be close enough to pick it up before you can examine it. */
struct SpellActionExamine
{
	SpellActionExamine() = default;
	virtual ~SpellActionExamine() = default;


	void Serialize(Serialization::IArchive& archive) { ; }
};


/** Take an item and place it in your inventory. */
struct SpellActionTake
{
	SpellActionTake() = default;
	virtual ~SpellActionTake() = default;


	void Serialize(Serialization::IArchive& archive) { ; }
};


/** Drop an inventory item that is equipped in your hand. */
struct SpellActionDrop
{
	SpellActionDrop() = default;
	virtual ~SpellActionDrop() = default;


	void Serialize(Serialization::IArchive& archive) { ; }
};


/** Throw an inventory item that is equipped in your hand. */
struct SpellActionThrow
{
	SpellActionThrow() = default;
	virtual ~SpellActionThrow() = default;


	void Serialize(Serialization::IArchive& archive) { ; }
};


/** Generic interaction for anything that can be switched from one state to another. */
struct SpellActionSwitch
{
	SpellActionSwitch() = default;
	virtual ~SpellActionSwitch() = default;


	void Serialize(Serialization::IArchive& archive) { ; }

	// TODO: Type of switch action - on, off, toggle
};


/** Generic interaction for anything that can be opened. */
struct SpellActionOpen
{
	SpellActionOpen() = default;
	virtual ~SpellActionOpen() = default;


	void Serialize(Serialization::IArchive& archive) { ; }
};


/** Generic interaction for anything that can be closed. */
struct SpellActionClose
{
	SpellActionClose() = default;
	virtual ~SpellActionClose() = default;


	void Serialize(Serialization::IArchive& archive) { ; }
};


/** Generic interaction for anything that can be unlocked. */
struct SpellActionUnlock
{
	SpellActionUnlock() = default;
	virtual ~SpellActionUnlock() = default;


	void Serialize(Serialization::IArchive& archive) { ; }
};


/** Generic interaction for anything that can be locked. */
struct SpellActionLock
{
	SpellActionLock() = default;
	virtual ~SpellActionLock() = default;


	void Serialize(Serialization::IArchive& archive) { ; }
};
}