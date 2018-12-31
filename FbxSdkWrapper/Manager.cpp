#include "stdafx.h"
#include "Manager.h"

using namespace System::Collections::Generic;
using namespace FbxWrapper;


static Manager::Manager()
{
	// Create the FBX SDK memory manager object.
	// The SDK Manager allocates and frees memory
	// for almost all the classes in the SDK.
	m_manager = FbxManager::Create();

	// create an IOSettings object
	FbxIOSettings * ios = FbxIOSettings::Create(m_manager, IOSROOT);
	m_manager->SetIOSettings(ios);


	m_importer = FbxImporter::Create(m_manager, "Importer");
	m_exporter = FbxExporter::Create(m_manager, "Exporter");

	//List<FileFormat2^>^ m_supported = gcnew List<FileFormat^>(1);

}

Manager::~Manager()
{
	m_importer->Destroy();
	m_exporter->Destroy();
	m_manager->Destroy();
}

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