#pragma once

#include "FileFormat.h"
#include "IOSetting.h"

namespace FbxWrapper
{
	public ref class Manager
	{
	public:
		static Manager();
		~Manager();

		// using List<> Generate compiling error 
		/// <summary>
		/// Plugin writer list, must be used to know the fileformatid when save file
		/// </summary> 
		static array<FileFormat^> ^GetSupportedWriters();
		/// <summary>
		/// Plugin reader list, must be used to know the fileformatid when open file.
		/// </summary> 
		static array<FileFormat^> ^GetSupportedReaders();
		/// <summary>
		/// Set the import-export states. By default, the export states are always set to
		/// true except for the option eEXPORT_TEXTURE_AS_EMBEDDED
		/// </summary> 
		static void SetIOProperty(IOProperty prop, bool value);

	internal:
		static FbxManager *m_manager;
		static FbxExporter *m_exporter;
	};
}
