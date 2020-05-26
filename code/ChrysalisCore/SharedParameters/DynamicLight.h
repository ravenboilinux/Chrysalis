#pragma once

#include <SharedParameters/SharedParameters.h>

class XmlNodeRef;

namespace Chrysalis
{
struct SDynamicLight : public ISharedParams
{
	SHARED_PARAMS_BODY(SDynamicLight);

	SDynamicLight() = default;
	virtual ~SDynamicLight() = default;

	/** Resets this object to it's default state. */
	virtual void Reset();

	/**
	Reads the given node.

	\param	node	The node to read.

	\return	true if it succeeds, false if it fails.
	*/
	virtual bool Read(const XmlNodeRef& node);

	/** Simple serialization of all of the members for this feature. Override if you need anything more complex. */
	void SerializeProperties(Serialization::IArchive& archive);

	/** Diffuse color expressed as RGB e.g. 128, 255, 128. */
	Vec3 diffuseColor {128.0f, 128.0f, 128.0f};

	/** Control the strength of the diffuse color. */
	float diffuseMultiplier {1.0f};

	/** Control the strength of the specular brightness. */
	float specularMultiplier {1.0f};

	/** Specifies how far from the source the light affects the surrounding area. */
	float radius {10.0f};

	/** Style variation (flickering, waxing / wanning / etc). */
	uint8 lightStyle {0};

	/** Rate at which the style animation will play .*/
	uint8 animationSpeed {1};

	/** Point in the cycle (style) at which light animation begins. */
	// TODO: Implement this value.
	uint8 lightPhase {0};


	// Projector.

	/** Specifies the Angle on which the light texture is projected .*/
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

	/** Specifies the radius of the area light bulb. */
	// TODO: Implement this value.
	float attenuationRadius {0.1f};
};

DECLARE_SHARED_POINTERS(SDynamicLight);
}