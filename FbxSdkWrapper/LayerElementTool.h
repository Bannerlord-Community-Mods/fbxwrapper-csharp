#pragma once
#include "stdafx.h"

namespace FbxWrapper
{

	template <class T>
	T* GetLayerElementTemplate(
		FbxMesh *mesh, 
		FbxLayerElementTemplate<T> *element,
		int &size)
	{

		if (!element) return nullptr;

		//Let's get normals of each vertex, since the mapping mode of normal element is by control point
		if (element->GetMappingMode() == FbxGeometryElement::eByControlPoint)
		{
			size = mesh->GetControlPointsCount();
			T *list = new T[size];

			for (int v = 0, n; v < size; v++)
			{
				//reference mode is direct, the normal index is same as vertex index.
				//get normals by the index of control vertex
				if (element->GetReferenceMode() == FbxGeometryElement::eDirect) n = v;
				//reference mode is index-to-direct, get normals by the index-to-direct
				if (element->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)n = element->GetIndexArray().GetAt(v);
				list[v] = element->GetDirectArray().GetAt(n);
			}
			return list;
		}
		//mapping mode is by polygon-vertex.we can get normals by retrieving polygon-vertex.
		else if (element->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
		{
			size = element->mDirectArray->GetCount(); //IS CORRECT ????
			T *list = new T[size];

			int idxByPolygon = 0;

			//Let's get normals of each polygon, since the mapping mode of normal element is by polygon-vertex.
			for (int p = 0; p < mesh->GetPolygonCount(); p++)
			{
				//get polygon size, you know how many vertices in current polygon.
				int polycount = mesh->GetPolygonSize(p);
				//retrieve each vertex of current polygon.

				for (int i = 0, n; i < polycount; i++)
				{
					//reference mode is direct, the normal index is same as lIndexByPolygonVertex.
					if (element->GetReferenceMode() == FbxGeometryElement::eDirect)
						n = idxByPolygon;

					//reference mode is index-to-direct, get normals by the index-to-direct
					if (element->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
						n = element->GetIndexArray().GetAt(idxByPolygon);

					if (idxByPolygon >= size)
						throw gcnew Exception("index of normal is out of range");

					list[idxByPolygon] = element->GetDirectArray().GetAt(n);

					idxByPolygon++;
				}
			}

		}
		//mapping mode is by polygon-vertex.we can get normals by retrieving polygon-vertex.
		else if (element->GetMappingMode() == FbxGeometryElement::eByPolygon)
		{
			size = mesh->GetPolygonCount();
			T *list = new T[size];

			//Let's get normals of each polygon, since the mapping mode of normal element is by polygon-vertex.
			for (int i = 0, n; i < size; i++)
			{
				//reference mode is direct, the normal index is same as lIndexByPolygonVertex.
				if (element->GetReferenceMode() == FbxGeometryElement::eDirect)
					n = i;

				//reference mode is index-to-direct, get normals by the index-to-direct
				if (element->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
					n = element->GetIndexArray().GetAt(i);

				list[i] = element->GetDirectArray().GetAt(n);
			}
			return list;
		}
		else
		{
			throw gcnew NotImplementedException("not implemented");
		}
		return nullptr;
	}


	template <class T>
	bool SetLayerElementTemplate(
		FbxMesh* mesh,
		FbxLayerElementTemplate<T> *element,
		T list[],
		int size,
		MappingMode mapping,
		ReferenceMode referencing)
	{
		element->SetMappingMode((FbxLayerElement::EMappingMode)mapping);
		element->SetReferenceMode((FbxLayerElement::EReferenceMode)referencing);

		//size = sizeof(list) / sizeof(list[0]);
		if (mapping == MappingMode::ByControlPoint)
		{
			int count = mesh->GetControlPointsCount();
			if (size > count)
				throw gcnew Exception("In ByControlPoint mapping mode, elements must be equal to (or less than) control points");

			if (referencing == ReferenceMode::Direct)
			{
				element->GetDirectArray().AddMultiple(count);
				for (int i = 0; i < count; i++)
				{
					element->GetDirectArray().SetAt(i, list[i]);
				}
			}
			else
			{
				throw gcnew NotImplementedException("not implemented");
			}

		}
		else if (mapping == MappingMode::ByPolygon)
		{
			int count = mesh->GetPolygonCount();
			if (size > count)
				throw gcnew Exception("In ByPolygon mapping mode, elements must be equal to (or less than) polygons");

			if (referencing == ReferenceMode::Direct)
			{
				element->GetDirectArray().AddMultiple(count);
				for (int i = 0; i < count; i++)
				{
					element->GetDirectArray().SetAt(i, list[i]);
				}
			}
			else
			{
				throw gcnew NotImplementedException("not implemented");
			}
		}
		else
		{
			throw gcnew NotImplementedException("not implemented");
		}
		return true;
	}
	
}

