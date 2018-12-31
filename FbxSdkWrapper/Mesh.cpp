#include "stdafx.h"
#include "Mesh.h"

using namespace FbxWrapper;

Mesh::Mesh(FbxMesh* pmesh)
{
	m_mesh = pmesh;
}

bool Mesh::Triangulated::get()
{
	return m_mesh->IsTriangleMesh();
}


MappingMode Mesh::GetMappingMode(LayerElementType elementType)
{
	FbxLayerElement::EType etype = (FbxLayerElement::EType)elementType;

	if (auto layer = m_mesh->GetLayer(0, etype))
	{
		return (MappingMode)layer->GetLayerElementOfType(etype)->GetMappingMode();
	}
	return MappingMode::None;
}

void Mesh::SetMappingMode(LayerElementType elementType, MappingMode mode)
{
	FbxLayerElement::EType etype = (FbxLayerElement::EType)elementType;
	
	if (auto layer = m_mesh->GetLayer(0, etype))
	{
		layer->GetLayerElementOfType(etype)->SetMappingMode((FbxLayerElement::EMappingMode)mode);
	}
}


#pragma region  Vertices


int Mesh::ControlPointsCount::get()
{
	return m_mesh->GetControlPointsCount();
}

void Mesh::ControlPointsCount::set(int count)
{
	if (count != m_mesh->GetControlPointsCount())
		m_mesh->SetControlPointCount(count);
}

bool Mesh::SetControlPointAt(int index, double x, double y, double z, double w)
{
	m_mesh->SetControlPointAt(FbxVector4(x, y, z, w), index);
	return index < m_mesh->GetControlPointsCount();
}

bool Mesh::GetControlPointAt(int index, float %x, float %y, float %z, float %w)
{
	FbxVector4 v = m_mesh->GetControlPointAt(index);
	x = v[0];
	y = v[1];
	z = v[2];
	w = v[3];
	return index < m_mesh->GetControlPointsCount();
}

Vector4 Mesh::GetControlPointAt(int index)
{
	return Vector4(m_mesh->GetControlPointAt(index));
}

array<Vector3> ^Mesh::ControlPoints::get()
{
	int count = m_mesh->GetControlPointsCount();
	auto list = gcnew array<Vector3>(count);
	for (int i = 0; i < count; i++)
		list[i] = Vector3(m_mesh->GetControlPointAt(i));
	return list;
}

void Mesh::ControlPoints::set(array<Vector3> ^controlpoints)
{
	int count = controlpoints->Length;
	for (int i = 0; i < count; i++)
	{
		Vector3 v = controlpoints[i];
		m_mesh->SetControlPointAt((FbxVector4)v, i);
	}
}

#pragma endregion

#pragma region Normals

array<Vector3> ^Mesh::Normals::get()
{
	auto element = m_mesh->GetLayer(0)->GetNormals();

	//Let's get normals of each vertex, since the mapping mode of normal element is by control point
	if (element->GetMappingMode() == FbxGeometryElement::eByControlPoint)
	{
		int count = m_mesh->GetControlPointsCount();
		auto list = gcnew array<Vector3>(count);

		for (int v = 0, n; v < count; v++)
		{
			//reference mode is direct, the normal index is same as vertex index.
			//get normals by the index of control vertex
			if (element->GetReferenceMode() == FbxGeometryElement::eDirect) n = v;
			//reference mode is index-to-direct, get normals by the index-to-direct
			if (element->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)n = element->GetIndexArray().GetAt(v);
			list[v] = Vector3(element->GetDirectArray().GetAt(n));
		}
	}
	//mapping mode is by polygon-vertex.we can get normals by retrieving polygon-vertex.
	else if (element->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
	{
		int count = element->mDirectArray->GetCount(); //IS CORRECT ????
		auto list = gcnew array<Vector3>(count);

		int idxByPolygon = 0;

		//Let's get normals of each polygon, since the mapping mode of normal element is by polygon-vertex.
		for (int p = 0; p < m_mesh->GetPolygonCount(); p++)
		{
			//get polygon size, you know how many vertices in current polygon.
			int size = m_mesh->GetPolygonSize(p);
			//retrieve each vertex of current polygon.
			
			for (int i = 0; i < size; i++)
			{
				int n = 0;
				//reference mode is direct, the normal index is same as lIndexByPolygonVertex.
				if (element->GetReferenceMode() == FbxGeometryElement::eDirect)
					n = idxByPolygon;

				//reference mode is index-to-direct, get normals by the index-to-direct
				if (element->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
					n = element->GetIndexArray().GetAt(idxByPolygon);

				if (idxByPolygon >= count)
					throw gcnew Exception("index of normal is out of range");

				list[idxByPolygon] = Vector3(element->GetDirectArray().GetAt(n));

				idxByPolygon++;
			}
		}
	}
}

void Mesh::Normals::set(array<Vector3> ^normals)
{
	auto element = m_mesh->GetLayer(0)->GetNormals();

	if (element->GetMappingMode() == FbxGeometryElement::eByControlPoint)
	{
		int count = m_mesh->GetControlPointsCount();
		if (normals->Length >count)
			throw gcnew Exception("In ByControlPoint mapping mode, normals elements must be equal to (or less than) control points");
		
		for (int v = 0, n; v < count; v++)
		{		
			if (element->GetReferenceMode() == FbxGeometryElement::eDirect) n = v;
			if (element->GetReferenceMode() == FbxGeometryElement::eIndexToDirect) n = element->GetIndexArray().GetAt(v);
			Vector3 vector = normals[v];
			element->GetDirectArray().SetAt(n, (FbxVector4)vector);
		}

	}
}
#pragma endregion

void Mesh::AddPolygon(array<int>^ indices)
{
	m_mesh->BeginPolygon(-1, -1, -1, false);	
	for each (int i in indices)
		m_mesh->AddPolygon(i);
	m_mesh->EndPolygon();
}

array<FbxWrapper::Polygon> ^Mesh::Polygons::get()
{
	int count = m_mesh->GetPolygonCount();
	auto list = gcnew array<Polygon>(count);

	for (int i = 0; i < count; i++)
	{
		auto poly = Polygon();

		int indexCount = m_mesh->GetPolygonSize(i);
		poly.Indices = gcnew array<int>(indexCount);

		for (int j = 0; j < indexCount; j++)
			poly.Indices[j] = m_mesh->GetPolygonVertex(i, j);

		list[i] = poly;
	}

	return list;
}

/*
array<Vector3> ^Mesh::Normals::get()
{
	auto normals = m_mesh->GetLayer(0)->GetNormals();
	int count = normals->GetDirectArray().GetCount();
	auto list = gcnew array<Vector3>(count);

	for (int i = 0; i < count; i++)
		list[i] = Vector3(normals->GetDirectArray().GetAt(i));

	return list;
}

array<Vector2> ^Mesh::TextureCoords::get()
{
	FbxLayer* layer = m_mesh->GetLayer(UVLayer);

	if (!layer)
		return gcnew array<Vector2>(0);

	auto coords = layer->GetUVs();
	int count = coords == nullptr ? 0 : coords->GetDirectArray().GetCount();
	auto list = gcnew array<Vector2>(count);

	for (int i = 0; i < count; i++)
		list[i] = Vector2(coords->GetDirectArray().GetAt(i));

	return list;
}

array<Vector3> ^Mesh::Tangents::get()
{
	auto tangents = m_mesh->GetLayer(0)->GetTangents();
	int count = tangents->GetDirectArray().GetCount();
	auto list = gcnew array<Vector3>(count);

	for (int i = 0; i < count; i++)
		list[i] = Vector3(tangents->GetDirectArray().GetAt(i));
	return list;
}

array<Colour> ^Mesh::VertexColours::get()
{
	auto colours = m_mesh->GetLayer(0)->GetVertexColors();
	int count = colours == nullptr ? 0 : colours->GetDirectArray().GetCount();
	auto list = gcnew array<Colour>(count);

	for (int i = 0; i < count; i++)
		list[i] = Colour(colours->GetDirectArray().GetAt(i));

	return list;
}

array<int> ^Mesh::MaterialIDs::get()
{
	auto materials = m_mesh->GetLayer(0)->GetMaterials();
	int count = materials == nullptr ? 0 : materials->GetIndexArray().GetCount();
	auto list = gcnew array<int>(count);

	for (int i = 0; i < count; i++)
		list[i] = materials->GetIndexArray().GetAt(i);

	return list;
}
*/