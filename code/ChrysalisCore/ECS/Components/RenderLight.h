#pragma once

#include <ECS/Components/Components.h>

// TEST:
#include <DefaultComponents/Lights/ILightComponent.h>


namespace Cry
{
namespace DefaultComponents
{
//void Serialize(Serialization::IArchive& archive, ILightComponent::SOptics& optics, const char* szName, const char* szLabel);
}
}


namespace Chrysalis::ECS
{
struct RenderLight : public IComponent
{
	RenderLight() = default;
	virtual ~RenderLight() = default;


	virtual const entt::hashed_string& GetHashedName() const
	{
		static constexpr entt::hashed_string nameHS {"render-light"_hs};

		return nameHS;
	}


	void Serialize(Serialization::IArchive& ar) override final
	{
		ar(diffuseColor, "diffuseColor", "Diffuse color expressed as RGB e.g. 128, 255, 128.");
		ar(diffuseMultiplier, "diffuseMultiplier", "Control the strength of the diffuse color.");
		ar(specularMultiplier, "specularMultiplier", "Control the strength of the specular brightness.");

		ar(radius, "radius", "Specifies how far from the source the light affects the surrounding area.");
		ar(lightStyle, "lightStyle", "Style variation (flickering, waxing / wanning / etc).");
		ar(animationSpeed, "animationSpeed", "Rate at which the style animation will play.");
		ar(lightPhase, "lightPhase", "Point in the cycle (style) at which light animation begins.");
		
		ar(shadowBias, "shadowBias", "Moves the shadow cascade toward or away from the shadow-casting object.");
		ar(shadowSlopeBias, "shadowSlopeBias", "Allows you to adjust the gradient (slope-based) bias used to compute the shadow bias.");
		ar(shadowResolutionScale, "shadowResolutionScale", "shadowResolutionScale");
		ar(shadowUpdateMinimumRadius, "shadowUpdateMinimumRadius", "Define the minimum radius from the light source to the player camera that the ShadowUpdateRatio setting will be ignored.");
		ar(shadowMinimumResolutionPercent, "shadowMinimumResolutionPercent", "Percentage of the shadow pool the light should use for its shadows.");
		ar(shadowUpdateRatio, "shadowUpdateRatio", "Define the update ratio for shadow maps cast from this light.");
		
		ar(effectSlotMaterial, "effectSlotMaterial", "A material for the effects slot.");
		ar(attenuationRadius, "attenuationRadius", "Specifies the radius of the light bulb.");

		//ar(optics, "optics", "optics");
	}


	//Cry::DefaultComponents::ILightComponent::SOptics optics;

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
	Schematyc::MaterialFileName effectSlotMaterial;

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


	void Serialize(Serialization::IArchive& ar) override final
	{
		ar(projectorFoV, "projectorFoV", "Specifies the Angle on which the light texture is projected.");
		ar(projectorTexture, "projectorTexture", " A texture to used for custom falloff.");
		ar(projectorFrustumAngle, "projectorFrustumAngle", "Frustum angle for the projected light / texture.");
		ar(projectorNearPlane, "projectorNearPlane", "Set the near plane for the projector, any surfaces closer to the light source than this value will not be projected on.");
	}

	/** Specifies the Angle on which the light texture is projected. */
	float projectorFoV {90.0f};

	/** A texture to used for custom falloff. */
	Schematyc::TextureFileName projectorTexture;

	/** Frustum angle for the projected light / texture. */
	// TODO: Implement this value.
	float projectorFrustumAngle {45.f};

	/** Set the near plane for the projector, any surfaces closer to the light source than this value will not be projected on. */
	// TODO: Implement this value.
	float projectorNearPlane {0.0f};
};
}