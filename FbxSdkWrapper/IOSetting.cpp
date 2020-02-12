#pragma managed

#include "stdafx.h"
#include "IOSetting.h"

using namespace FbxWrapper;


IOSetting::IOSetting()
{
	throw gcnew System::NotImplementedException();
}

IOSetting::IOSetting(FbxManager *m_manager)
{
	// create an IOSettings object
	m_ios = FbxIOSettings::Create(m_manager, IOSROOT);
	m_manager->SetIOSettings(m_ios);
}

bool IOSetting::GetProperty()
{
	return false;
}
void IOSetting::SetProperty(bool value)
{

}