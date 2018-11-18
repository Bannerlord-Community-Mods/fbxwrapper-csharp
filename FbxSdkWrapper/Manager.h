#pragma once

namespace FbxWrapper
{
	public ref class Manager sealed
	{
	public:
		static Manager();
		static FbxManager *GetInstance();
		static FbxImporter *GetImporter();
		static FbxExporter *GetExporter();

	private:
		static FbxManager * m_manager;
		static FbxImporter *m_importer;
		static FbxExporter *m_exporter;
	};
}
