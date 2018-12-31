#pragma once

#include "FileFormat.h"

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

	internal:
		static FbxManager *m_manager;
		static FbxImporter *m_importer;
		static FbxExporter *m_exporter;
	};
}
