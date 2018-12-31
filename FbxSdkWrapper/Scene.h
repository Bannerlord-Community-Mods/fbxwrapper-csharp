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
		Scene(string ^name);
		/// <summary>
		/// Import a supported fbx file defined by fileformatID (-1 if autodetect) found with
		/// Manager.GetSupportedReaders list
		/// </summary>
		static Scene ^Import(string ^filepath, int fileformat);
		/// <summary>
		/// Export a supported fbx file defined by fileformatID (-1 for native writer... i don't known that it's)
		/// found with Manager.GetSupportedWriters list
		/// </summary>
		static void Export(Scene ^scene, string ^filepath, int fileFormat);
		
		property_r(Node^, RootNode);

		// file version from importer, will be stored to remember when exporting
		property Version^ FileVersion;

	private:
		FbxScene *m_scene;
		Node ^m_rootNode;
		FbxManager *m_manager;
	};
}

