#pragma once

#include "Polygon.h"
#include "LayerElementTool.h"

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
		/// Get how the layer element (normals, texture, etc...) are stored.
		/// http://docs.autodesk.com/FBX/2014/ENU/FBX-SDK-Documentation/index.html?url=cpp_ref/_normals_2main_8cxx-example.html,topicNumber=cpp_ref__normals_2main_8cxx_example_html2cff27fd-bb1a-4142-982e-65fd5d6ad951
		/// If ByControlPoint the n'th element match with n'th control point
		/// </summary>
		MappingMode GetMappingMode(LayerElementType layer);
		/// <summary>
		/// </summary>
		//void SetMappingMode(LayerElementType elementType, MappingMode mode);

		/// <summary>
		/// Gets and sets the control points size, if size is different the items are not cleaned !
		/// </summary>
		property_rw(int, ControlPointsCount);
		/// <summary>
		/// sets the vertices, if index is out of limit, the array is resize internaly but function return if success 
		/// </summary>
		bool SetControlPointAt(int index, double x, double y, double z);
		/// <summary>
		/// get the vertices, if index is out of range, zero vector is returned
		/// </summary>
		Vector3 Mesh::GetControlPointAt(int index);
		
		property_rw(array<Vector3>^, ControlPoints);
		
		/// <summary>
		/// Gets the normal from layer 0
		/// </summary>
		array<Vector3>^ GetNormals();
		/// <summary>
		/// Gets the tangents from layer 0
		/// </summary>
		array<Vector3>^ GetTangents();
		/// <summary>
		/// Set element in layer 0. A new layer element will be create, the old element are deleted
		/// </summary>
		bool SetNormals(array<Vector3>^ normals, MappingMode mapping, ReferenceMode referencing);
		/// <summary>
		/// Set element in layer 0. A new layer element will be create, the old element are deleted
		/// </summary>
		bool SetTangents(array<Vector3>^ tangents, MappingMode mapping, ReferenceMode referencing);


		void AddPolygon(array<int> ^indices);
		property_r(array<Polygon>^, Polygons);

		//property_r(array<Vector2>^, TextureCoords);
		//property_r(array<Colour>^, VertexColours);
		//property_r(array<Vector3>^, Tangents);
		//property_r(array<int>^, MaterialIDs);
		property_r(bool, Triangulated);
		
		property int UVLayer;

	};
}
