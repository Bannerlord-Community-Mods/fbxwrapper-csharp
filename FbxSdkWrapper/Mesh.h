#pragma once

#include "Polygon.h"

using namespace System::Collections::Generic;

namespace FbxWrapper
{
	public ref class Mesh
	{
	private:
		FbxMesh * m_mesh;
	internal:
		Mesh(FbxMesh* pmesh);

	public:
		/// <summary>
		/// Gets and sets the control points size, if size is different the items are not cleaned !
		/// </summary>
		property_rw(int, ControlPointsCount);
		/// <summary>
		/// sets the vertices, if index is out of limit, the array is resize internaly
		/// </summary>
		void SetControlPointAt(double x, double y, double z, double w, int index);

		void AddPolygon(array<int> ^indices);

		property_r(array<Polygon>^, Polygons);
		property_r(array<Vector3>^, Vertices);
		property_r(array<Vector3>^, Normals);
		property_r(array<Vector2>^, TextureCoords);
		property_r(array<Colour>^, VertexColours);
		property_r(array<Vector3>^, Tangents);
		property_r(array<int>^, MaterialIDs);
		property_r(bool, Triangulated);
		
		property int UVLayer;

	};
}
