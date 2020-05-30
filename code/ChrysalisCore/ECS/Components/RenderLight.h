#pragma once

#include <ECS/Components/Components.h>

// HACK: TEST: Checking if it's possible / worth it to add serialize functions to the existing default component structures.
#include <DefaultComponents/Lights/ILightComponent.h>


namespace Cry
{
namespace DefaultComponents
{
/** We need to add a Serialize function for each type, since they lack one. */
bool Serialize(Serialization::IArchive& ar, ILightComponent::SOptions& desc, const char* szName, const char* szLabel);
bool Serialize(Serialization::IArchive& ar, ILightComponent::SColor& desc, const char* szName, const char* szLabel);
bool Serialize(Serialization::IArchive& ar, ILightComponent::SOptics& desc, const char* szName, const char* szLabel);
bool Serialize(Serialization::IArchive& ar, ILightComponent::SShadows& desc, const char* szName, const char* szLabel);
bool Serialize(Serialization::IArchive& ar, ILightComponent::SAnimations& desc, const char* szName, const char* szLabel);
bool Serialize(Serialization::IArchive& ar, ILightComponent::SShape& desc, const char* szName, const char* szLabel);
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
		ar(optics, "optics", "optics");
		ar(options, "options", "options");
		ar(color, "color", "color");
		ar(shadows, "shadows", "shadows");
		ar(animations, "animations", "animations");
		ar(shape, "shape", "shape");

		ar(radius, "radius", "Specifies how far from the source the light affects the surrounding area.");
		ar(attenuationRadius, "attenuationRadius", "Specifies the radius of the light bulb.");
		ar(effectSlotMaterial, "effectSlotMaterial", "A material for the effects slot.");
	}


	/** Using the default components CryTek provided. This will help with compatibility down the line. */
	Cry::DefaultComponents::ILightComponent::SOptions options;
	Cry::DefaultComponents::ILightComponent::SColor color;
	Cry::DefaultComponents::ILightComponent::SOptics optics;
	Cry::DefaultComponents::ILightComponent::SShadows shadows;
	Cry::DefaultComponents::ILightComponent::SAnimations animations;
	Cry::DefaultComponents::ILightComponent::SShape shape;

	/** Specifies how far from the source the light affects the surrounding area. */
	float radius {10.0f};

	/** Specifies the radius of the light bulb. */
	// TODO: Implement this value.
	float attenuationRadius {0.1f};

	/** A material for the effects slot. */
	Schematyc::MaterialFileName effectSlotMaterial;
};


struct ProjectorLight : public IComponent
{
	ProjectorLight() = default;
	ProjectorLight(float projectorFoV, Schematyc::TextureFileName projectorTexture, float projectorFrustumAngle, float projectorNearPlane)
		: projectorFoV(projectorFoV), projectorTexture(projectorTexture), projectorFrustumAngle(projectorFrustumAngle), projectorNearPlane(projectorNearPlane) {};

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