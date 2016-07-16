#include <StdAfx.h>

#include "ItemGeometryParameter.h"
#include <GameXmlParamReader.h>
#include <Game/Game.h>
#include <Game/Cache/GameCache.h>
#include <Item/Parameters/ItemParameter.h>


CItemGeometryParameter::CItemGeometryParameter()
{
	
}


CItemGeometryParameter::~CItemGeometryParameter()
{
}


void CItemGeometryParameter::Reset()
{
	*this = CItemGeometryParameter();
}


bool CItemGeometryParameter::Read(const XmlNodeRef& node)
{
	CGameXmlParamReader reader(node);

	// Read the parameters.
	modelPath = reader.ReadParamValue("modelPath");
	material = reader.ReadParamValue("material");
	reader.ReadParamValue("position", position);
	reader.ReadParamValue("angles", angles);
	reader.ReadParamValue("scale", scale);
	reader.ReadParamValue("slot", slot);
	reader.ReadParamValue("useCgfStreaming", useCgfStreaming);
	reader.ReadParamValue("useParentMaterial", useParentMaterial);

	return true;
}

