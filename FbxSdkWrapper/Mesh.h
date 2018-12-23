#pragma once

#include "Polygon.h"

namespace FbxWrapper
{
	public ref class Mesh
	{
	private:
		FbxMesh * m_mesh;
	internal:
		Mesh(FbxMesh* pmesh);

	public:
		property_r(array<Polygon>^, Polygons);
		property_r(array<Vector3>^, Vertices);
		property_r(array<Vector3>^, Normals);
		property_r(array<Vector2>^, TextureCoords);
		property_r(array<Colour>^, VertexColours);
		property_r(array<int>^, MaterialIDs);
		property_r(bool, Triangulated);
		property int UVLayer;

	};
}
