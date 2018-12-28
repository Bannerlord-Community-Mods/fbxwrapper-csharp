#include "stdafx.h"
#include "Scene.h"

using namespace System;
using namespace System::Runtime::InteropServices;

using namespace FbxWrapper;

Scene::Scene()
{
	m_scene = FbxScene::Create(Manager::m_manager, nullptr);
	m_rootNode = gcnew Node(m_scene->GetRootNode());
}
Scene::Scene(string ^name)
{
	m_scene = FbxScene::Create(Manager::m_manager, StringHelper::ToNative(name));
	m_rootNode = gcnew Node(m_scene->GetRootNode());
}

void Scene::Export(Scene^ scene, string^ filename, FileFormat format)
{
	FbxExporter* exporter = Manager::m_exporter;
	if (!exporter->Initialize(StringHelper::ToNative(filename), (int)format, exporter->GetIOSettings()))
		throw gcnew FbxException("Failed to initialize the FBX exporter: {0}", gcnew string(exporter->GetStatus().GetErrorString()));

	FbxIOFileHeaderInfo *infoExporter = exporter->GetFileHeaderInfo();
	infoExporter->mCreator = "Johnwhile FbxWrapper Exporter";

	//exporter->SetFileExportVersion(FBX_FILE_VERSION_6000);

	if (!exporter->Export(scene->m_scene))
		throw gcnew FbxException("Failed to export the scene: {0}", gcnew string(exporter->GetStatus().GetErrorString()));

}

Scene ^Scene::Import(string ^filename)
{
	FbxImporter* importer = Manager::m_importer;

	if (!importer->Initialize(StringHelper::ToNative(filename), -1, importer->GetIOSettings()))
		throw gcnew FbxException("Failed to initialise the FBX importer: {0}", gcnew string(importer->GetStatus().GetErrorString()));

	Scene^ scene = gcnew Scene("");

	// Populate the FBX file format version numbers with the import file.
	int lFileMajor, lFileMinor, lFileRevision;
	importer->GetFileVersion(lFileMajor, lFileMinor, lFileRevision);
	scene->FileVersion = gcnew Version(lFileMajor, lFileMinor, 0, lFileRevision);

	if (!importer->Import(scene->m_scene))
		throw gcnew FbxException("Failed to import the scene: {0}", gcnew string(importer->GetStatus().GetErrorString()));

	// Needs refreshing
	scene->m_rootNode = gcnew Node(scene->m_scene->GetRootNode());

	return scene;
}

Node ^Scene::RootNode::get()
{
	return m_rootNode;
}