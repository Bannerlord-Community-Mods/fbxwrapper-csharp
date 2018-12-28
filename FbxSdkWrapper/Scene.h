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
		/// <summary>
		/// Initialize a new scene with its name, root node are created automatically
		/// </summary> 
		Scene();
		Scene(string ^name);
		static Scene ^Import(string ^filepath);
		static void Export(Scene ^scene, string ^filepath, FileFormat format);
		
		property_r(Node^, RootNode);
		// file version from importer, will be stored to remember when exporting
		property Version^ FileVersion;

	private:
		FbxScene *m_scene;
		Node ^m_rootNode;
		FbxManager *m_manager;
	};
}

