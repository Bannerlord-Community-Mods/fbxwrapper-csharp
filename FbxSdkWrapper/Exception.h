#pragma once

namespace FbxWrapper
{
	public ref class FbxException : public System::Exception
	{
	public:
		FbxException(System::String ^message, ...array<Object^> ^args) : Exception(System::String::Format(message, args))
		{
		}
	};
}