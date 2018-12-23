#pragma once

#include "stdafx.h"
#include "NodeAttribute.h"
#include "Mesh.h"

//using namespace System::Collections::Generic;

namespace FbxWrapper
{
	/// <summary>
	/// Basic scene's node hierarchy
	/// </summary> 
	public ref class Node
	{
	public:

		//property string^ Name {string^ get(); }
		property_r(string^, Name);

		/// <summary>
		/// For root node this member is NULL
		/// </summary>
		property_r(NodeAttribute^, Node::Attribute);

		/// <summary>
		/// Gets and sets the position of this node.
		/// </summary>
		property_rw(Vector3, Position);

		/// <summary>
		/// Gets and sets the rotation of this node.
		/// </summary>
		property_rw(Vector3, Rotation);

		/// <summary>
		/// Gets and sets the scale of this node.
		/// </summary>
		property_rw(Vector3, Scale);

		/// <summary>
		/// Gets the first mesh attribute of this node if it exists, otherwise null.
		/// </summary>
		property_r(FbxWrapper::Mesh^, Mesh);

		int GetChildCount();
		Node ^GetChild(int index);

	internal:
		Node(FbxNode *pnode);
		FbxNode *m_node;

	};
}
