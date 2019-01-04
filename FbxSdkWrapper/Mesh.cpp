#include "stdafx.h"
#include "Mesh.h"

using namespace FbxWrapper;
using namespace System::Diagnostics;


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


#pragma region Vertices

int Mesh::ControlPointsCount::get()
{
	return m_mesh->GetControlPointsCount();
}

void Mesh::ControlPointsCount::set(int count)
{
	if (count != m_mesh->GetControlPointsCount())
		m_mesh->SetControlPointCount(count);
}

bool Mesh::SetControlPointAt(int index, double x, double y, double z)
{
	m_mesh->SetControlPointAt(FbxVector4(x, y, z, 0), index);
	return index < m_mesh->GetControlPointsCount();
}

Vector3 Mesh::GetControlPointAt(int index)
{
	return Vector3(m_mesh->GetControlPointAt(index));
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


bool Mesh::SetNormals(array<Vector3>^ normals, MappingMode mapping, ReferenceMode referencing)
{
	// Set the normals on Layer 0.
	auto layer0 = m_mesh->GetLayer(0);
	if (layer0 == NULL)
	{
		m_mesh->CreateLayer();
		layer0 = m_mesh->GetLayer(0);
	}
	FbxLayerElementTemplate<FbxVector4> *normalLayer = FbxLayerElementNormal::Create(m_mesh, "normals");
	int size = normals->Length;
	FbxVector4 *list = new FbxVector4[size];
	for (int i = 0; i < size; i++)
	{
		Vector3 n = normals[i];
		list[i] = (FbxVector4)n;
	}
	SetLayerElementTemplate<FbxVector4>(m_mesh, normalLayer, list, size, mapping, referencing);
	layer0->SetLayerElementOfType(normalLayer, FbxLayerElement::EType::eNormal);
	return true;
}

bool Mesh::SetTangents(array<Vector3>^ tangents, MappingMode mapping, ReferenceMode referencing)
{
	// Set the normals on Layer 0.
	auto layer0 = m_mesh->GetLayer(0);
	if (layer0 == NULL)
	{
		m_mesh->CreateLayer();
		layer0 = m_mesh->GetLayer(0);
	}
	FbxLayerElementTemplate<FbxVector4> *tangentLayer = FbxLayerElementTangent::Create(m_mesh, "tangents");
	int size = tangents->Length;
	FbxVector4 *list = new FbxVector4[size];
	for (int i = 0; i < size; i++)
	{
		Vector3 n = tangents[i];
		list[i] = (FbxVector4)n;
	}
	SetLayerElementTemplate<FbxVector4>(m_mesh, tangentLayer, list, size, mapping, referencing);
	layer0->SetLayerElementOfType(tangentLayer, FbxLayerElement::EType::eTangent);
	return true;
}

array<Vector3> ^Mesh::GetNormals()
{
	auto layer0 = m_mesh->GetLayer(0);
	if (layer0 == NULL) return nullptr;

	array<Vector3> ^vectors = nullptr;
	int size;
	FbxVector4* plist = GetLayerElementTemplate<FbxVector4>(m_mesh, layer0->GetNormals(), size);
	if (plist)
	{
	    vectors = gcnew array<Vector3>(size);
		for (int i = 0; i < size; i++) vectors[i] = Vector3(plist[i]);
	}
	return vectors;
}

array<Vector3> ^Mesh::GetTangents()
{
	auto layer0 = m_mesh->GetLayer(0);
	if (layer0 == NULL) return nullptr;

	array<Vector3> ^vectors = nullptr;
	int size;
	FbxVector4* plist = GetLayerElementTemplate<FbxVector4>(m_mesh, layer0->GetTangents(), size);
	if (plist)
	{
		vectors = gcnew array<Vector3>(size);
		for (int i = 0; i < size; i++) vectors[i] = Vector3(plist[i]);
	}
	return vectors;
}

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