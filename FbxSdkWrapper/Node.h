#pragma once

#include "stdafx.h"
#include "NodeAttribute.h"

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

		/// <summary> For root node this member is NULL</summary> 
		property_r(NodeAttribute^, Attribute);
		//property NodeAttribute^ Attribute {NodeAttribute^ get(); }

		int GetChildCount();
		Node ^GetChild(int index);

	internal:
		Node(FbxNode *pnode);
		FbxNode *m_node;
	};
}
