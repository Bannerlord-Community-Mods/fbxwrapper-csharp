#pragma once

#include "Properties.h"
#include "Node.h"
#include "Manager.h"

namespace FbxWrapper
{
	/// <summary>
	/// Represents an FBX scene.
	/// </summary>
	public ref class Scene
	{
	public:
		Scene(string ^name);
		static Scene ^Import(string ^filepath);
		
		property Node^ RootNode {Node^ get(); }
		//property_r(Node^, RootNode);

	private:
		FbxScene *m_scene;
		Node ^m_rootNode;
		FbxManager *m_manager;
	};
}

