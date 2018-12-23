#include "stdafx.h"
#include "Node.h"

using namespace FbxWrapper;

Node::Node(FbxNode *pnode)
{
	m_node = pnode;
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


Vector3 Node::Position::get()
{
	return Vector3(m_node->LclTranslation.Get());
}
void Node::Position::set(Vector3 value)
{
	m_node->LclTranslation.Set(value);
}

Vector3 Node::Rotation::get()
{
	return Vector3(m_node->LclRotation.Get());
}
void Node::Rotation::set(Vector3 value)
{
	m_node->LclRotation.Set(value);
}

Vector3 Node::Scale::get()
{
	return Vector3(m_node->LclScaling.Get());
}
void Node::Scale::set(Vector3 value)
{
	m_node->LclScaling.Set(value);
}

Mesh ^Node::Mesh::get()
{
	return gcnew FbxWrapper::Mesh(m_node->GetMesh());
}