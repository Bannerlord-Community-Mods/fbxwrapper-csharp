#pragma once

#include "Manager.h"

namespace FbxWrapper
{
	/// <summary>
	/// Represents the input-output setting
	/// </summary>
	public ref class IOSetting sealed
	{
	public:
		IOSetting();
		IOSetting(FbxManager *m_manager);
		FbxIOSettings * m_ios;
	public:
		bool GetProperty();
		void SetProperty(bool value);
	};

}