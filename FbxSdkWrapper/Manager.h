#pragma once

namespace FbxWrapper
{
	public ref class Manager sealed
	{
	public:
		static Manager();

	internal:
		static FbxManager * m_manager;
		static FbxImporter *m_importer;
		static FbxExporter *m_exporter;
	};
}
