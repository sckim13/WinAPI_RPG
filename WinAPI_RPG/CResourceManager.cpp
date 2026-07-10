#include "pch.h"
#include "CResourceManager.h"
#include "CPathManager.h"
#include "CTexture.h"
#include "Struct.h"

vector<TTextureInfo> g_TextureSource =
{
    // UI
    TTextureInfo {L"Monster",       ETextureType::BMP, L"Texture\\Monster"},
    TTextureInfo {L"Player",        ETextureType::BMP, L"Texture\\Player"},
    TTextureInfo {L"Inventory",     ETextureType::PNG, L"Texture\\Inventory"},
    TTextureInfo {L"Equipment",     ETextureType::PNG, L"Texture\\Equipment"},
    TTextureInfo {L"Cursor",        ETextureType::BMP, L"Texture\\Cursor"},
    TTextureInfo {L"ActiveSkill",   ETextureType::PNG, L"Texture\\ActiveSkill"},
    TTextureInfo {L"Item",          ETextureType::BMP, L"Texture\\Item"},

    // Damage Skin
    TTextureInfo {L"Damage_Red_Normal_0",    ETextureType::PNG, L"Texture\\UI\\Damage\\Default\\Normal\\0.effect.NoRed1.0"},
    TTextureInfo {L"Damage_Red_Normal_1",    ETextureType::PNG, L"Texture\\UI\\Damage\\Default\\Normal\\0.effect.NoRed1.1"},
    TTextureInfo {L"Damage_Red_Normal_2",    ETextureType::PNG, L"Texture\\UI\\Damage\\Default\\Normal\\0.effect.NoRed1.2"},
    TTextureInfo {L"Damage_Red_Normal_3",    ETextureType::PNG, L"Texture\\UI\\Damage\\Default\\Normal\\0.effect.NoRed1.3"},
    TTextureInfo {L"Damage_Red_Normal_4",    ETextureType::PNG, L"Texture\\UI\\Damage\\Default\\Normal\\0.effect.NoRed1.4"},
    TTextureInfo {L"Damage_Red_Normal_5",    ETextureType::PNG, L"Texture\\UI\\Damage\\Default\\Normal\\0.effect.NoRed1.5"},
    TTextureInfo {L"Damage_Red_Normal_6",    ETextureType::PNG, L"Texture\\UI\\Damage\\Default\\Normal\\0.effect.NoRed1.6"},
    TTextureInfo {L"Damage_Red_Normal_7",    ETextureType::PNG, L"Texture\\UI\\Damage\\Default\\Normal\\0.effect.NoRed1.7"},
    TTextureInfo {L"Damage_Red_Normal_8",    ETextureType::PNG, L"Texture\\UI\\Damage\\Default\\Normal\\0.effect.NoRed1.8"},
    TTextureInfo {L"Damage_Red_Normal_9",    ETextureType::PNG, L"Texture\\UI\\Damage\\Default\\Normal\\0.effect.NoRed1.9"},
    TTextureInfo {L"Damage_Red_Normal_man",  ETextureType::PNG, L"Texture\\UI\\Damage\\Default\\Normal\\208.effect.NoCustom.NoRed1.3"},
    TTextureInfo {L"Damage_Red_Normal_eok",  ETextureType::PNG, L"Texture\\UI\\Damage\\Default\\Normal\\208.effect.NoCustom.NoRed1.4"},
    TTextureInfo {L"Damage_Red_Normal_miss", ETextureType::PNG, L"Texture\\UI\\Damage\\Default\\Normal\\0.effect.NoRed0.Miss"},
    TTextureInfo {L"Damage_Red_Cri_0",       ETextureType::PNG, L"Texture\\UI\\Damage\\Default\\Critical\\0.effect.NoCri1.0"},
    TTextureInfo {L"Damage_Red_Cri_1",       ETextureType::PNG, L"Texture\\UI\\Damage\\Default\\Critical\\0.effect.NoCri1.1"},
    TTextureInfo {L"Damage_Red_Cri_2",       ETextureType::PNG, L"Texture\\UI\\Damage\\Default\\Critical\\0.effect.NoCri1.2"},
    TTextureInfo {L"Damage_Red_Cri_3",       ETextureType::PNG, L"Texture\\UI\\Damage\\Default\\Critical\\0.effect.NoCri1.3"},
    TTextureInfo {L"Damage_Red_Cri_4",       ETextureType::PNG, L"Texture\\UI\\Damage\\Default\\Critical\\0.effect.NoCri1.4"},
    TTextureInfo {L"Damage_Red_Cri_5",       ETextureType::PNG, L"Texture\\UI\\Damage\\Default\\Critical\\0.effect.NoCri1.5"},
    TTextureInfo {L"Damage_Red_Cri_6",       ETextureType::PNG, L"Texture\\UI\\Damage\\Default\\Critical\\0.effect.NoCri1.6"},
    TTextureInfo {L"Damage_Red_Cri_7",       ETextureType::PNG, L"Texture\\UI\\Damage\\Default\\Critical\\0.effect.NoCri1.7"},
    TTextureInfo {L"Damage_Red_Cri_8",       ETextureType::PNG, L"Texture\\UI\\Damage\\Default\\Critical\\0.effect.NoCri1.8"},
    TTextureInfo {L"Damage_Red_Cri_9",       ETextureType::PNG, L"Texture\\UI\\Damage\\Default\\Critical\\0.effect.NoCri1.9"},
    TTextureInfo {L"Damage_Red_Cri_man",     ETextureType::PNG, L"Texture\\UI\\Damage\\Default\\Critical\\208.effect.NoCustom.NoCri1.3"},
    TTextureInfo {L"Damage_Red_Cri_eok",     ETextureType::PNG, L"Texture\\UI\\Damage\\Default\\Critical\\208.effect.NoCustom.NoCri1.4"},

    // Map
    TTextureInfo {L"map_background1",   ETextureType::PNG, L"Texture\\map_background1"},
    TTextureInfo {L"map_front1",        ETextureType::PNG, L"Texture\\map_front1"},
};

vector<int> g_DamageSkinSource =
{

};

CResourceManager::CResourceManager()
{

}

CResourceManager::~CResourceManager()
{
    Release();
}

void CResourceManager::Initialize()
{
    const wstring strBasetPath = CPathManager::GetInstance()->GetBasePath();

    for (auto& format : g_TextureSource)
    {
        auto [strKey, eType, strRelPath] = format;

        CTexture* pTexture = new CTexture;

        pTexture->SetType(eType);
        pTexture->SetKey(strKey);
        pTexture->SetRelativePath(strRelPath);

        wstring strAssetPath = strBasetPath + strRelPath;
        
        switch(eType)
        {
        case ETextureType::BMP:
            pTexture->LoadBMP(strAssetPath + L".bmp");
            break;
        case ETextureType::PNG:
            pTexture->LoadPNG(strAssetPath + L".png");
            break;
        default:
            assert(0);
            break;
            
        }

        m_mapTexture.insert({ strKey, pTexture });
    }
}

void CResourceManager::PostInitialize()
{
}

void CResourceManager::Update()
{
}

void CResourceManager::LateUpdate()
{
}

void CResourceManager::Release()
{
    for (auto& pair : m_mapTexture)
    {
        Safe_Delete(pair.second);
    }
    m_mapTexture.clear();
}

void CResourceManager::Render(HDC hDC)
{
}

CTexture* CResourceManager::LoadTexture(const wstring& strKey)
{
    CTexture* pTexture = FindTexture(strKey);
    assert(pTexture);
    if (pTexture)
    {
        return pTexture;
    }

    return nullptr;
 
    //wstring strAssetPath = CPathManager::GetInstance()->GetBasePath();
    //strAssetPath += strRelPath;

    ///* TODO : assert when there is no Texture on the texture map */
    //pTexture = new CTexture;
    //pTexture->SetKey(strKey);
    //pTexture->SetRelativePath(strRelPath);
    //pTexture->Load(strAssetPath);

    //m_mapTexture.insert({strKey, pTexture});

    //return pTexture;
}

CTexture* CResourceManager::FindTexture(const wstring& strKey)
{
    auto iter = m_mapTexture.find(strKey);
    if (iter != m_mapTexture.end())
    {
        return iter->second;
    }
    else
    {
        return nullptr;
    }
}

void CResourceManager::GetMapData(const wstring& wstrPath)
{
}
