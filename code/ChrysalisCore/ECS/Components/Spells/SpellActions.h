#pragma once

#include "ECS/Components/Components.h"


namespace Chrysalis::ECS
{
/** Raise a schematyc event. */
struct SpellActionSchematyc : public IComponent
{
	SpellActionSchematyc() = default;
	virtual ~SpellActionSchematyc() = default;


	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"schematyc"_hs};

		return nameHS;
	}


	bool Serialize(Serialization::IArchive& archive) override final
	{
		return true;
	}
};


/** Raise a DRS event. */
struct SpellActionDRS : public IComponent
{
	SpellActionDRS() = default;
	virtual ~SpellActionDRS() = default;


	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"drs"_hs};

		return nameHS;
	}


	bool Serialize(Serialization::IArchive& archive) override final
	{
		return true;
	}
};


/** Take a closer look at some environmental feature e.g. a time clock for punching into work. */
struct SpellActionInspect : public IComponent
{
	SpellActionInspect() = default;
	virtual ~SpellActionInspect() = default;


	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"inspect"_hs};

		return nameHS;
	}


	bool Serialize(Serialization::IArchive& archive) override final
	{
		return true;
	}
};

/** Examine an item while holding it in your hands. You should be close enough to pick it up before you can examine it. */
struct SpellActionExamine : public IComponent
{
	SpellActionExamine() = default;
	virtual ~SpellActionExamine() = default;


	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"examine"_hs};

		return nameHS;
	}


	bool Serialize(Serialization::IArchive& archive) override final
	{
		return true;
	}
};


/** Take an item and place it in your inventory. */
struct SpellActionTake : public IComponent
{
	SpellActionTake() = default;
	virtual ~SpellActionTake() = default;


	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"take"_hs};

		return nameHS;
	}


	bool Serialize(Serialization::IArchive& archive) override final
	{
		return true;
	}
};


/** Drop an inventory item that is equipped in your hand. */
struct SpellActionDrop : public IComponent
{
	SpellActionDrop() = default;
	virtual ~SpellActionDrop() = default;


	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"drop"_hs};

		return nameHS;
	}


	bool Serialize(Serialization::IArchive& archive) override final
	{
		return true;
	}
};


/** Throw an inventory item that is equipped in your hand. */
struct SpellActionThrow : public IComponent
{
	SpellActionThrow() = default;
	virtual ~SpellActionThrow() = default;


	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"throw"_hs};

		return nameHS;
	}


	bool Serialize(Serialization::IArchive& archive) override final
	{
		return true;
	}
};


/** Generic interaction for anything that can be switched from one state to another. */
struct SpellActionSwitch : public IComponent
{
	SpellActionSwitch() = default;
	virtual ~SpellActionSwitch() = default;


	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"switch"_hs};

		return nameHS;
	}


	bool Serialize(Serialization::IArchive& archive) override final
	{
		return true;
	}

	// TODO: Type of switch action - on, off, toggle
};


/** Generic interaction for anything that can be opened. */
struct SpellActionOpen : public IComponent
{
	SpellActionOpen() = default;
	virtual ~SpellActionOpen() = default;


	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"open"_hs};

		return nameHS;
	}


	bool Serialize(Serialization::IArchive& archive) override final
	{
		return true;
	}
};


/** Generic interaction for anything that can be closed. */
struct SpellActionClose : public IComponent
{
	SpellActionClose() = default;
	virtual ~SpellActionClose() = default;


	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"close"_hs};

		return nameHS;
	}


	bool Serialize(Serialization::IArchive& archive) override final
	{
		return true;
	}
};


/** Generic interaction for anything that can be unlocked. */
struct SpellActionUnlock : public IComponent
{
	SpellActionUnlock() = default;
	virtual ~SpellActionUnlock() = default;


	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"unlock"_hs};

		return nameHS;
	}


	bool Serialize(Serialization::IArchive& archive) override final
	{
		return true;
	}
};


/** Generic interaction for anything that can be locked. */
struct SpellActionLock : public IComponent
{
	SpellActionLock() = default;
	virtual ~SpellActionLock() = default;


	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"lock"_hs};

		return nameHS;
	}


	bool Serialize(Serialization::IArchive& archive) override final
	{
		return true;
	}
};
}