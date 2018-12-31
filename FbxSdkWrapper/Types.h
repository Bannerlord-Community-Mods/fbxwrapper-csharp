#pragma once

namespace FbxWrapper
{
	// The types that are to be used for the attributes
	public enum class AttributeType : int
	{
		eUnknown,
		eNull,
		eMarker,
		eSkeleton,
		eMesh,
		eNurbs,
		ePatch,
		eCamera,
		eCameraStereo,
		eCameraSwitcher,
		eLight,
		eOpticalReference,
		eOpticalMarker,
		eNurbsCurve,
		eTrimNurbsSurface,
		eBoundary,
		eNurbsSurface,
		eShape,
		eLODGroup,
		eSubDiv,
		eCachedEffect,
		eLine
	};
	
	/// <summary>
	/// Layer Type (EType)
	/// </summary>
	public enum class LayerElementType : int
	{
		eUnknown,

		//Non-Texture layer element types
		//Note: Make sure to update static index below if you change this enum!
		eNormal,
		eBiNormal,
		eTangent,
		eMaterial,
		ePolygonGroup,
		eUV,
		eVertexColor,
		eSmoothing,
		eVertexCrease,
		eEdgeCrease,
		eHole,
		eUserData,
		eVisibility,

		//Texture layer element types
		//Note: Make sure to update static index below if you change this enum!
		eTextureDiffuse,
		eTextureDiffuseFactor,
		eTextureEmissive,
		eTextureEmissiveFactor,
		eTextureAmbient,
		eTextureAmbientFactor,
		eTextureSpecular,
		eTextureSpecularFactor,
		eTextureShininess,
		eTextureNormalMap,
		eTextureBump,
		eTextureTransparency,
		eTextureTransparencyFactor,
		eTextureReflection,
		eTextureReflectionFactor,
		eTextureDisplacement,
		eTextureDisplacementVector,

		eTypeCount
	};
}