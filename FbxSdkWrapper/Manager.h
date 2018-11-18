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
		static FbxManager * m_nativeManager;
		static FbxImporter *m_nativeImporter;
		static FbxExporter *m_nativeExporter;
	};
}
