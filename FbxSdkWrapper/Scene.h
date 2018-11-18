#pragma once

#include "SceneNode.h"

namespace FbxWrapper
{
	/// <summary>
	/// Represents an FBX scene.
	/// </summary>
	ref class Scene
	{
	public:
		Scene(string ^name);

	private:
		FbxScene * m_nativeScene;
		SceneNode ^m_rootNode;
		FbxManager *m_manager;
	};
}

