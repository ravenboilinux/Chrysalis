#pragma once

#include "ECS/Components/Components.h"


namespace Chrysalis::ECS
{
/** Raise a schematyc event. */
struct SpellActionSchematyc : public IComponent
{
	SpellActionSchematyc() = default;
	virtual ~SpellActionSchematyc() = default;


	void Serialize(Serialization::IArchive& archive) override final { ; }
};


/** Raise a DRS event. */
struct SpellActionDRS : public IComponent
{
	SpellActionDRS() = default;
	virtual ~SpellActionDRS() = default;


	void Serialize(Serialization::IArchive& archive) override final { ; }
};


/** Take a closer look at some environmental feature e.g. a time clock for punching into work. */
struct SpellActionInspect : public IComponent
{
	SpellActionInspect() = default;
	virtual ~SpellActionInspect() = default;


	void Serialize(Serialization::IArchive& archive) override final { ; }
};

/** Examine an item while holding it in your hands. You should be close enough to pick it up before you can examine it. */
struct SpellActionExamine : public IComponent
{
	SpellActionExamine() = default;
	virtual ~SpellActionExamine() = default;


	void Serialize(Serialization::IArchive& archive) override final { ; }
};


/** Take an item and place it in your inventory. */
struct SpellActionTake : public IComponent
{
	SpellActionTake() = default;
	virtual ~SpellActionTake() = default;


	void Serialize(Serialization::IArchive& archive) override final { ; }
};


/** Drop an inventory item that is equipped in your hand. */
struct SpellActionDrop : public IComponent
{
	SpellActionDrop() = default;
	virtual ~SpellActionDrop() = default;


	void Serialize(Serialization::IArchive& archive) override final { ; }
};


/** Throw an inventory item that is equipped in your hand. */
struct SpellActionThrow : public IComponent
{
	SpellActionThrow() = default;
	virtual ~SpellActionThrow() = default;


	void Serialize(Serialization::IArchive& archive) override final { ; }
};


/** Generic interaction for anything that can be switched from one state to another. */
struct SpellActionSwitch : public IComponent
{
	SpellActionSwitch() = default;
	virtual ~SpellActionSwitch() = default;


	void Serialize(Serialization::IArchive& archive) override final { ; }

	// TODO: Type of switch action - on, off, toggle
};


/** Generic interaction for anything that can be opened. */
struct SpellActionOpen : public IComponent
{
	SpellActionOpen() = default;
	virtual ~SpellActionOpen() = default;


	void Serialize(Serialization::IArchive& archive) override final { ; }
};


/** Generic interaction for anything that can be closed. */
struct SpellActionClose : public IComponent
{
	SpellActionClose() = default;
	virtual ~SpellActionClose() = default;


	void Serialize(Serialization::IArchive& archive) override final { ; }
};


/** Generic interaction for anything that can be unlocked. */
struct SpellActionUnlock : public IComponent
{
	SpellActionUnlock() = default;
	virtual ~SpellActionUnlock() = default;


	void Serialize(Serialization::IArchive& archive) override final { ; }
};


/** Generic interaction for anything that can be locked. */
struct SpellActionLock : public IComponent
{
	SpellActionLock() = default;
	virtual ~SpellActionLock() = default;


	void Serialize(Serialization::IArchive& archive) override final { ; }
};
}