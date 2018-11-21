#include "stdafx.h"
#include "NodeAttribute.h"

using namespace FbxWrapper;

NodeAttribute::NodeAttribute(FbxNodeAttribute* attribute)
{
	m_attribute = attribute;
}

AttributeType NodeAttribute::Type::get()
{
	return (AttributeType)m_attribute->GetAttributeType();
}
