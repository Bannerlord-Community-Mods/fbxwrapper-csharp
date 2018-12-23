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

array<Vector3> ^Mesh::Vertices::get()
{
	int count = m_mesh->GetControlPointsCount();
	auto list = gcnew array<Vector3>(count);

	for (int i = 0; i < count; i++)
	{
		auto point = m_mesh->GetControlPointAt(i);
		list[i] = Vector3(point);
	}

	return list;
}

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