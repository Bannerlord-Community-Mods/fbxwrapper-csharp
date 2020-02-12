#pragma once

namespace FbxWrapper
{
	public ref class NodeAttribute
	{
	internal:
		NodeAttribute(FbxNodeAttribute* attribute);
		FbxNodeAttribute *m_attribute;
	public:
		property_r(AttributeType, Type);
	};
}

