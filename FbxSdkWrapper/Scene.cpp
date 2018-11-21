#include "stdafx.h"
#include "Scene.h"

using namespace System;
using namespace System::Runtime::InteropServices;

using namespace FbxWrapper;


Scene::Scene(string ^name)
{
	m_scene = FbxScene::Create(Manager::m_manager, StringHelper::ToNative(name));
	m_rootNode = gcnew Node(m_scene->GetRootNode());
}

Scene ^Scene::Import(string ^filename)
{
	FbxImporter* importer = Manager::m_importer;

	if (!importer->Initialize(StringHelper::ToNative(filename), -1, importer->GetIOSettings()))
		throw gcnew FbxException("Failed to initialise the FBX importer: {0}", gcnew string(importer->GetStatus().GetErrorString()));

	auto scene = gcnew Scene("");

	// File format version numbers to be populated.
	int lFileMajor, lFileMinor, lFileRevision;

	// Populate the FBX file format version numbers with the import file.
	importer->GetFileVersion(lFileMajor, lFileMinor, lFileRevision);

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