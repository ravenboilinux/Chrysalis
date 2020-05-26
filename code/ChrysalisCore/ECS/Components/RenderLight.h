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
		archive(diffuseColor, "diffuseColor", "Diffuse color expressed as RGB e.g. 128, 255, 128.");
		archive(diffuseMultiplier, "diffuseMultiplier", "Control the strength of the diffuse color.");
		archive(specularMultiplier, "specularMultiplier", "Control the strength of the specular brightness.");

		archive(radius, "radius", "Specifies how far from the source the light affects the surrounding area.");
		archive(lightStyle, "lightStyle", "Style variation (flickering, waxing / wanning / etc).");
		archive(animationSpeed, "animationSpeed", "Rate at which the style animation will play.");
		archive(lightPhase, "lightPhase", "Point in the cycle (style) at which light animation begins.");
		
		archive(projectorFoV, "projectorFoV", "Specifies the Angle on which the light texture is projected.");
		archive(projectorTexture, "projectorTexture", " A texture to used for custom falloff.");
		archive(projectorFrustumAngle, "projectorFrustumAngle", "Frustum angle for the projected light / texture.");
		archive(projectorNearPlane, "projectorNearPlane", "Set the near plane for the projector, any surfaces closer to the light source than this value will not be projected on.");
		
		archive(shadowBias, "shadowBias", "Moves the shadow cascade toward or away from the shadow-casting object.");
		archive(shadowSlopeBias, "shadowSlopeBias", "Allows you to adjust the gradient (slope-based) bias used to compute the shadow bias.");
		archive(shadowResolutionScale, "shadowResolutionScale", "shadowResolutionScale");
		archive(shadowUpdateMinimumRadius, "shadowUpdateMinimumRadius", "Define the minimum radius from the light source to the player camera that the ShadowUpdateRatio setting will be ignored.");
		archive(shadowMinimumResolutionPercent, "shadowMinimumResolutionPercent", "Percentage of the shadow pool the light should use for its shadows.");
		archive(shadowUpdateRatio, "shadowUpdateRatio", "Define the update ratio for shadow maps cast from this light.");
		
		archive(effectSlotMaterial, "effectSlotMaterial", "A material for the effects slot.");
		archive(attenuationRadius, "attenuationRadius", "Specifies the radius of the light bulb.");

		return true;
	}

	/** Diffuse color expressed as RGB e.g. 128, 255, 128. */
	Vec3 diffuseColor {128.0f, 128.0f, 128.0f};

	/** Control the strength of the diffuse color.*/
	float diffuseMultiplier {1.0f};

	/** Control the strength of the specular brightness. */
	float specularMultiplier {1.0f};

	/** Specifies how far from the source the light affects the surrounding area. */
	float radius {10.0f};

	/** Style variation (flickering, waxing / wanning / etc). */
	uint8 lightStyle {0};

	/** Rate at which the style animation will play. */
	uint8 animationSpeed {1};

	/** Point in the cycle (style) at which light animation begins. */
	// TODO: Implement this value.
	uint8 lightPhase {0};


	// Projector.

	/** Specifies the Angle on which the light texture is projected. */
	float projectorFoV {90.0f};

	/** A texture to used for custom falloff. */
	string projectorTexture;

	/** Frustum angle for the projected light / texture. */
	// TODO: Implement this value.
	float projectorFrustumAngle {45.f};

	/** Set the near plane for the projector, any surfaces closer to the light source than this value will not be projected on. */
	// TODO: Implement this value.
	float projectorNearPlane {0.0f};


	// Shadow map fields.

	/** Moves the shadow cascade toward or away from the shadow-casting object. */
	// TODO: Implement this value.
	float shadowBias {1.0f};

	/** Allows you to adjust the gradient (slope-based) bias used to compute the shadow bias. */
	// TODO: Implement this value.
	float shadowSlopeBias {1.0f};

	/** */
	// TODO: Implement this value.
	float shadowResolutionScale {1.0f};

	/** Define the minimum radius from the light source to the player camera that the ShadowUpdateRatio setting will be ignored. */
	// TODO: Implement this value.
	float shadowUpdateMinimumRadius {4.0f};

	/** Percentage of the shadow pool the light should use for its shadows. */
	// TODO: Implement this value.
	uint16 shadowMinimumResolutionPercent {0};

	/** Define the update ratio for shadow maps cast from this light. */
	// TODO: Implement this value.
	uint16 shadowUpdateRatio {1 << DL_SHADOW_UPDATE_SHIFT};


	// Misc.

	/** A material for the effects slot. */
	string effectSlotMaterial;

	/** Specifies the radius of the light bulb. */
	// TODO: Implement this value.
	float attenuationRadius {0.1f};
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