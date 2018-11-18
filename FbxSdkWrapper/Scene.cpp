#include "stdafx.h"
#include "Scene.h"
#include "Manager.h"

using namespace System;
using namespace System::Runtime::InteropServices;

using namespace FbxWrapper;


Scene::Scene(string ^name)
{
	const char* pname = StringHelper::ToNative(name);

	//IntPtr pname = Marshal::StringToHGlobalAnsi(name);
	//Marshal::FreeHGlobal(pname);
	//m_nativeScene = FbxScene::Create(Manager::GetInstance(), pname.ToPointer());
	//m_rootNode = gcnew SceneNode(m_nativeScene->GetRootNode());
}

