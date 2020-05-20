#pragma once

//#include "Utility\ItemString.h"
//#include <CryMath/Cry_Vector3.h>
//#include <SharedParameters/SharedParameters.h>



namespace Chrysalis::ECS
{
//enum class DamageType
//{
//	acid,
//	bleed,
//	cold,
//	collision,
//	cleave,
//	crush,
//	decay,
//	disease,
//	electricity,
//	energy,
//	entropy,
//	explosion,
//	fire,
//	holy,
//	ice,
//	nature,
//	pierce,
//	plasma,
//	poison,
//	qi,
//	radiation,
//	slash,
//	tear,
//	unholy
//};


struct RenderLight : public IComponent
{
	RenderLight() = default;
	virtual ~RenderLight() = default;


	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"render-light"_hs};

		return nameHS;
	}


	bool Serialize(Serialization::IArchive& archive) override final
	{
		archive(style, "style", "style");
		archive(lightColour, "lightColour", "lightColour");
		archive(specularMultiplier, "specularMultiplier", "specularMultiplier");

		return true;
	}

	/** The style of light which will be created e.g. steady, flickering, etc. */
	uint8 style {0};

	/** The light colour. */
	Vec3 lightColour {1.0f, 1.0f, 1.0f};

	/** The specular multiplier. */
	float specularMultiplier {1.0f};

	///** The diffuse multiplier. */
	//float diffuseMultiplier;

	///** The distance. */
	//float distance;

	///** Field of view. */
	//float fieldOfView;

	///** The animation speed. */
	//float animationSpeed;

	///** The fog volume colour. */
	//Vec3 fogVolumeColour;

	///** The fog volume radius. */
	//float fogVolumeRadius;

	///** Size of the fog volume. */
	//float fogVolumeSize;

	///** The fog volume density. */
	//float fogVolumeDensity;

	///** The light cookie. */
	//string lightCookie;
};


struct ProjectorLight : public IComponent
{
	ProjectorLight() = default;
	virtual ~ProjectorLight() = default;


	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"projector-light"_hs};

		return nameHS;
	}


	bool Serialize(Serialization::IArchive& archive) override final
	{
		archive(nearPlane, "nearPlane", "nearPlane");
		archive(texturePath, "texturePath", "texturePath");
		archive(materialPath, "materialPath", "materialPath");

		return true;
	}


	Schematyc::Range<0, 10000> nearPlane {0.0f};
	Schematyc::TextureFileName texturePath;
	Schematyc::MaterialFileName materialPath;
};
}