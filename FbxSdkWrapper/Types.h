#pragma once

namespace FbxWrapper
{
	/// <summary>
	/// Use it when exporting fbx, by default all prop are set to true
	/// </summary>
	public enum class IOProperty
	{
		Exp_FBX_MATERIAL,
		Exp_FBX_TEXTURE,
		Exp_FBX_EMBEDDED,
		Exp_FBX_SHAPE,
		Exp_FBX_GOBO,
		Exp_FBX_ANIMATION,
		Exp_FBX_GLOBAL_SETTINGS
	};

	// The types that are to be used for the attributes
	public enum class AttributeType : int
	{
		Unknown,
		Null,
		Marker,
		Skeleton,
		Mesh,
		Nurbs,
		Patch,
		Camera,
		CameraStereo,
		CameraSwitcher,
		Light,
		OpticalReference,
		OpticalMarker,
		NurbsCurve,
		TrimNurbsSurface,
		Boundary,
		NurbsSurface,
		Shape,
		LODGroup,
		SubDiv,
		CachedEffect,
		Line
	};
	

	/// <summary>
	/// Determines how the element is mapped to a surface.
	/// </summary>
	public enum class MappingMode
	{
		/// <summary>
		/// not implemented
		/// </summary>
		None,
		/// <summary>
		/// There will be one mapping coordinate for each surface control point / vertex..
		/// </summary>
		ByControlPoint,
		/// <summary>
		/// There will be one mapping coordinate for each vertex, for every polygon of which it is a part.
		/// </summary>
		ByPolygonVertex,
		/// <summary>
		/// There can be only one mapping coordinate for the whole polygon.
		/// </summary>
		ByPolygon,
		/// <summary>
		/// not implemented
		/// </summary>
		ByEdge,
		/// <summary>
		/// not implemented
		/// </summary>
		AllSame
	};
	
	/// <summary>
	/// Determines how the mapping information is stored in the array of coordinates.
	/// </summary>
	public enum class ReferenceMode
	{
		Direct,
		Index,
		IndexToDirect
	};

	/// <summary>
	/// Layer Type (EType)
	/// </summary>
	public enum class LayerElementType : int
	{
		Unknown,

		//Non-Texture layer element types
		//Note: Make sure to update static index below if you change this enum!
		Normal,
		BiNormal,
		Tangent,
		Material,
		PolygonGroup,
		UV,
		VertexColor,
		Smoothing,
		VertexCrease,
		EdgeCrease,
		Hole,
		UserData,
		Visibility,

		//Texture layer element types
		//Note: Make sure to update static index below if you change this enum!
		TextureDiffuse,
		TextureDiffuseFactor,
		TextureEmissive,
		TextureEmissiveFactor,
		TextureAmbient,
		TextureAmbientFactor,
		TextureSpecular,
		TextureSpecularFactor,
		TextureShininess,
		TextureNormalMap,
		TextureBump,
		TextureTransparency,
		TextureTransparencyFactor,
		TextureReflection,
		TextureReflectionFactor,
		TextureDisplacement,
		TextureDisplacementVector,

		TypeCount
	};
	
}