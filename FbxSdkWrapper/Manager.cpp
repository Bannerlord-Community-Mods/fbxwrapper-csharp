#include "stdafx.h"
#include "Manager.h"
#include "IOSetting.h"

using namespace System::Collections::Generic;
using namespace FbxWrapper;


static Manager::Manager()
{
	// Create the FBX SDK memory manager object.
	// The SDK Manager allocates and frees memory
	// for almost all the classes in the SDK.
	m_manager = FbxManager::Create();

	// create an IOSettings object
	// create an IOSettings object
	FbxIOSettings* m_iosetting = FbxIOSettings::Create(m_manager, IOSROOT);
	m_manager->SetIOSettings(m_iosetting);

	m_importer = FbxImporter::Create(m_manager, "Importer");
	m_exporter = FbxExporter::Create(m_manager, "Exporter");
}

Manager::~Manager()
{
	m_importer->Destroy();
	m_exporter->Destroy();
	m_manager->Destroy();
}
/*
IOSetting ^Manager::InOutSetting::get()
{
	return m_iosetting;
}
*/
array<FileFormat^> ^Manager::GetSupportedWriters()
{
	int count = m_manager->GetIOPluginRegistry()->GetWriterFormatCount();
	
	array<FileFormat^> ^list = gcnew array<FileFormat^>(count);

	for (int i = 0; i < count; i++)
	{
		FileFormat^ file = gcnew FileFormat();
		file->Description = gcnew String(m_manager->GetIOPluginRegistry()->GetWriterFormatDescription(i));
		file->Extension = gcnew String(m_manager->GetIOPluginRegistry()->GetWriterFormatExtension(i));
		list[i] = file;
	}
	return list;
}

array<FileFormat^> ^Manager::GetSupportedReaders()
{
	int count = m_manager->GetIOPluginRegistry()->GetReaderFormatCount();
	array<FileFormat^> ^list = gcnew array<FileFormat^>(count);
	for (int i = 0; i < count; i++)
	{
		FileFormat^ file = gcnew FileFormat();
		file->Description = gcnew String(m_manager->GetIOPluginRegistry()->GetReaderFormatDescription(i));
		file->Extension = gcnew String(m_manager->GetIOPluginRegistry()->GetReaderFormatExtension(i));
		list[i] = file;
	}
	return list;
}

void Manager::SetIOProperty(IOProperty prop, bool value)
{
	FbxIOSettings* io = m_manager->GetIOSettings();
	char* name;
	switch (prop)
	{
		case IOProperty::Exp_FBX_MATERIAL: name = EXP_FBX_MATERIAL; break;
		case IOProperty::Exp_FBX_TEXTURE: name = EXP_FBX_TEXTURE; break;
		case IOProperty::Exp_FBX_EMBEDDED: name = EXP_FBX_EMBEDDED; break;
		case IOProperty::Exp_FBX_SHAPE: name = EXP_FBX_SHAPE; break;
		case IOProperty::Exp_FBX_GOBO: name = EXP_FBX_GOBO; break;
		case IOProperty::Exp_FBX_ANIMATION: name = EXP_FBX_ANIMATION; break;
		case IOProperty::Exp_FBX_GLOBAL_SETTINGS: name = EXP_FBX_GLOBAL_SETTINGS; break;
		default: name = NULL;
	}
	io->SetBoolProp(name, value);

}
