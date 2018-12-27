#pragma once

namespace FbxWrapper
{
	// The types that are to be used for the attributes
	public enum class AttributeType
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
	public enum class FileFormat : int
	{
		Null = -1,

		FbxBinary = 0,
		FbxAscii = 1,
		FbxEncrypted = 2,
		Fbx5Binary = 3,
		Fbx5Ascii = 4,
		AutocadDXF = 5,
		StudioMax3DS = 6,
		AliasOBJ = 7,
		ColladaDAE = 8
	};
}