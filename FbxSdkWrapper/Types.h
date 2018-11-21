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
}