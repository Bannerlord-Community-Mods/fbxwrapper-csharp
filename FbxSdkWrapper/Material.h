#pragma once
#include "Polygon.h"
#include "LayerElementTool.h"
#include "Types.h"

using namespace System::Collections::Generic;

namespace FbxWrapper
{
    public ref class Material
    {
    public:
        Material(FbxSurfaceMaterial* p_mat) {
            this->m_mat = p_mat;

        }
        array<string^>^ TexturePaths(LayerElementType type) {
            const char* proptype = "";
            switch (type) {
            case LayerElementType::TextureDiffuse:
                proptype = FbxSurfaceMaterial::sDiffuse;
                break;
            case LayerElementType::TextureBump:
                proptype = FbxSurfaceMaterial::sBump;
                break;
            case LayerElementType::TextureEmissive:
                proptype = FbxSurfaceMaterial::sEmissive;
                break;
            case LayerElementType::TextureReflection:
                proptype = FbxSurfaceMaterial::sReflection;
                break;
            case LayerElementType::TextureAmbient:
                proptype = FbxSurfaceMaterial::sAmbient;
                break;
            case LayerElementType::TextureNormalMap:
                proptype = FbxSurfaceMaterial::sNormalMap;
                break;
            case LayerElementType::TextureSpecular:
                proptype = FbxSurfaceMaterial::sSpecular;
                break;
            }
            FbxProperty prop = this->m_mat->FindProperty(proptype);
            int nonlayeredTextureCount = prop.GetSrcObjectCount<FbxTexture>();
            int layeredTextureCount = prop.GetSrcObjectCount<FbxLayeredTexture>();
            std::vector<const char*> texNames = std::vector<const char*>();
            int texCount = 0;
            if (layeredTextureCount > 0)
            {
                for (int j = 0; j < layeredTextureCount; j++)
                {
                    FbxLayeredTexture* layered_texture = FbxCast<FbxLayeredTexture>(prop.GetSrcObject<FbxLayeredTexture>(j));
                    int lcount = layered_texture->GetSrcObjectCount<FbxTexture>();

                    for (int k = 0; k < lcount; k++)
                    {
                        FbxFileTexture* texture = FbxCast<FbxFileTexture>(layered_texture->GetSrcObject<FbxTexture>(k));
                        // Then, you can get all the properties of the texture, include its name
                        texNames.push_back(texture->GetFileName());
                        texCount++;
                    }
                }
            }
            else {
                int textureCount = prop.GetSrcObjectCount<FbxTexture>();
                for (int j = 0; j < textureCount; j++)
                {
                    FbxFileTexture* texture = FbxCast<FbxFileTexture>(prop.GetSrcObject<FbxTexture>(j));
                    // Then, you can get all the properties of the texture, include its name


                    texNames.push_back(texture->GetFileName());
                    texCount++;



                }

            }
            array<string^>^ result = gcnew array<string^>(texCount);
            for (int i = 0; i < texCount; i++)
            {
                auto texName = texNames[i];
                result[i] = gcnew string(texName);
            }
            return result;
        }
    private:
        FbxSurfaceMaterial* m_mat;
    };
}

