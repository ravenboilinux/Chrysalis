#include <StdAfx.h>

#include "RenderLight.h"


namespace Cry
{
namespace DefaultComponents
{
bool Serialize(Serialization::IArchive& ar, ILightComponent::SOptics& optics, const char* szName, const char* szLabel)
{
	ar(optics.m_lensFlareName, "m_lensFlareName", "Diffuse color expressed as RGB e.g. 128, 255, 128.");
	ar(optics.m_attachToSun, "m_attachToSun", "Control the strength of the diffuse color.");
	ar(optics.m_flareEnable, "m_flareEnable", "Control the strength of the specular brightness.");
	ar(optics.m_flareFOV, "m_flareFOV", "Control the strength of the specular brightness.");

	return true;
}
}
}


namespace Chrysalis::ECS
{
}
