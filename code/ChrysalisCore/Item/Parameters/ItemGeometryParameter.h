#pragma once

class XmlNodeRef;

namespace Chrysalis
{
// #TODO: Dig into the code to find out what this does.
enum eGeometrySlot
{
	eIGS_FirstPerson = 0,		// First person character.
	eIGS_ThirdPerson,			// Third person character.
	eIGS_Owner,					// Mostly used in item code. Appears in weapon code.
	eIGS_OwnerAnimGraph,		// Deprecated (probably).
	eIGS_OwnerAnimGraphLooped,	// Deprecated (probably).
	eIGS_Aux0,					// Gun turrets and items.
	eIGS_Destroyed,				// Gun turret and item resource.
	eIGS_Aux1,					// Gun turret, item, laser.
	eIGS_ThirdPersonAux,		// Item, JAW, laser.
	eIGS_Last,					// End of reserved slot list.
};


class CItemGeometryParameter
{
public:
	CItemGeometryParameter();
	~CItemGeometryParameter();


	/** Full pathname of the model file. */
	string modelPath;

	/** The material. */
	string material;

	/** The position. */
	Vec3 position { Vec3(0.0f, 0.0f, 0.0f) };

	/** The angles. */
	Ang3 angles { Ang3(0.0f, 0.0f, 0.0f) };

	/** The scale. */
	float scale { 1.0f };

	/** The slot. */
	int slot { eGeometrySlot::eIGS_Last };

	/** true to use CGF streaming. */
	bool useCgfStreaming { false };

	/** true to use parent material. */
	bool useParentMaterial { false };


	/** Resets this object to it's default state. */
	virtual void OnResetState();

	/**
	Reads the given node.

	\param	node	The node to read.

	\return	true if it succeeds, false if it fails.
	*/
	bool Read(const XmlNodeRef& node);
};
}