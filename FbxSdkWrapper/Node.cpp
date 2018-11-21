#include "stdafx.h"
#include "Node.h"

using namespace FbxWrapper;

Node::Node(FbxNode *pnode)
{
	m_node = pnode;

	/*m_children = gcnew List<SceneNode^>();
	m_attributes = gcnew List<NodeAttribute^>();

	for (int i = 0; i < m_nativeNode->GetChildCount(); i++)
	{
		auto sub = m_nativeNode->GetChild(i);
		m_children->Add(gcnew SceneNode(sub));
	}

	for (int i = 0; i < m_nativeNode->GetNodeAttributeCount(); i++)
	{
		auto attr = m_nativeNode->GetNodeAttributeByIndex(i);
		m_attributes->Add(gcnew NodeAttribute(attr));
	}
	*/
}

string ^Node::Name::get()
{
	return gcnew string(m_node->GetName());
}

NodeAttribute ^Node::Attribute::get()
{
	FbxNodeAttribute *a = m_node->GetNodeAttribute();

	if (a == nullptr)
	{
		//throw gcnew FbxException("Native node attribute is null");
		return nullptr;
	}
	return gcnew NodeAttribute(m_node->GetNodeAttribute());
}

int Node::GetChildCount()
{
	return m_node->GetChildCount(false);
}

Node ^Node::GetChild(int index)
{
	return gcnew Node(m_node->GetChild(index));
}