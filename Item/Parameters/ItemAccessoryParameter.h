#pragma once

class XmlNodeRef;


class CItemAccessoryParameter
{
public:
	CItemAccessoryParameter();
	~CItemAccessoryParameter();


	/** Resets this object to it's default state. */
	void Reset();

	/**
	Reads the given node.

	\param	node	The node to read.

	\return	true if it succeeds, false if it fails.
	*/
	bool Read(const XmlNodeRef& node);
};

