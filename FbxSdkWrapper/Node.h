#pragma once

#include "stdafx.h"

namespace FbxWrapper
{
	public ref class Node
	{
	public:
		property_r(string^, Name);
		
		int GetChildCount();
		Node ^GetChild(int index);

	internal:
		Node(FbxNode *pnode);
		FbxNode *m_node;
	};
}
