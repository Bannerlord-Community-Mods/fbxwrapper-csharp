// stdafx.h : file di inclusione per file di inclusione di sistema standard
// o file di inclusione specifici del progetto utilizzati di frequente, ma
// modificati raramente

#pragma once

#define FBXSDK_NEW_API

#include <fbxsdk.h>
#include <msclr/marshal_cppstd.h>

typedef System::String string;



using namespace msclr::interop;

static ref class StringHelper
{
public:
	static const char *ToNative(System::String ^string)
	{
		if (!m_context)
			m_context = gcnew marshal_context();

		return m_context->marshal_as<const char*>(string);
	}

private:
	static marshal_context ^m_context;
};