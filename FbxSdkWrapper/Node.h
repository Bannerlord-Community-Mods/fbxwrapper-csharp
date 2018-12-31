#pragma once

#include "stdafx.h"
#include "NodeAttribute.h"
#include "Mesh.h"
#include "Manager.h"

//using namespace System::Collections::Generic;

namespace FbxWrapper
{
	/// <summary>
	/// Basic scene's node hierarchy.
	/// Represents an element in the scene graph. A scene graph is a tree of FbxNode objects.
	/// </summary> 
	public ref class Node
	{
	public:

		Node(AttributeType etype, string^ name);

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
		// (node attribute casted to a FbxMesh pointer)
		/// </summary>
		property_r(FbxWrapper::Mesh^, Mesh);

		int GetChildCount();
		Node ^GetChild(int index);

		void AddChild(Node ^node);

	internal:
		Node(FbxNode *pnode);
		FbxNode *m_node;

	};
}
