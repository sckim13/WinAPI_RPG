#include "pch.h"
#include "CResourceManager.h"
#include "CPathManager.h"
#include "CTexture.h"

map<const wstring, const wstring> g_TextureSource =
{
    {L"Monster", L"Texture\\Monster.bmp"},
    {L"Player", L"Texture\\Player.bmp"},
    {L"Inventory", L"Texture\\Inventory.bmp"},
    {L"Equipment", L"Texture\\Equipment.bmp"},
    {L"Cursor", L"Texture\\Cursor.bmp"},
    {L"ActiveSkill", L"Texture\\ActiveSkill.bmp"},
    {L"Item", L"Texture\\Item.bmp"},

    // Damage
    {L"Damage_Red_Normal_0", L"Texture\\UI\\Damage\\Normal\\0.effect.NoRed1.0.bmp"},
    {L"Damage_Red_Normal_1", L"Texture\\UI\\Damage\\Normal\\0.effect.NoRed1.1.bmp"},
    {L"Damage_Red_Normal_2", L"Texture\\UI\\Damage\\Normal\\0.effect.NoRed1.2.bmp"},
    {L"Damage_Red_Normal_3", L"Texture\\UI\\Damage\\Normal\\0.effect.NoRed1.3.bmp"},
    {L"Damage_Red_Normal_4", L"Texture\\UI\\Damage\\Normal\\0.effect.NoRed1.4.bmp"},
    {L"Damage_Red_Normal_5", L"Texture\\UI\\Damage\\Normal\\0.effect.NoRed1.5.bmp"},
    {L"Damage_Red_Normal_6", L"Texture\\UI\\Damage\\Normal\\0.effect.NoRed1.6.bmp"},
    {L"Damage_Red_Normal_7", L"Texture\\UI\\Damage\\Normal\\0.effect.NoRed1.7.bmp"},
    {L"Damage_Red_Normal_8", L"Texture\\UI\\Damage\\Normal\\0.effect.NoRed1.8.bmp"},
    {L"Damage_Red_Normal_9", L"Texture\\UI\\Damage\\Normal\\0.effect.NoRed1.9.bmp"},
    {L"Damage_Red_Normal_man", L"Texture\\UI\\Damage\\Normal\\208.effect.NoCustom.NoRed1.3.bmp"},
    {L"Damage_Red_Normal_eok", L"Texture\\UI\\Damage\\Normal\\208.effect.NoCustom.NoRed1.4.bmp"},
    {L"Damage_Red_Normal_miss", L"Texture\\UI\\Damage\\Normal\\0.effect.NoRed0.Miss.bmp"},
    {L"Damage_Red_Cri_0", L"Texture\\UI\\Damage\\Critical\\0.effect.NoCri1.0.bmp"},
    {L"Damage_Red_Cri_1", L"Texture\\UI\\Damage\\Critical\\0.effect.NoCri1.1.bmp"},
    {L"Damage_Red_Cri_2", L"Texture\\UI\\Damage\\Critical\\0.effect.NoCri1.2.bmp"},
    {L"Damage_Red_Cri_3", L"Texture\\UI\\Damage\\Critical\\0.effect.NoCri1.3.bmp"},
    {L"Damage_Red_Cri_4", L"Texture\\UI\\Damage\\Critical\\0.effect.NoCri1.4.bmp"},
    {L"Damage_Red_Cri_5", L"Texture\\UI\\Damage\\Critical\\0.effect.NoCri1.5.bmp"},
    {L"Damage_Red_Cri_6", L"Texture\\UI\\Damage\\Critical\\0.effect.NoCri1.6.bmp"},
    {L"Damage_Red_Cri_7", L"Texture\\UI\\Damage\\Critical\\0.effect.NoCri1.7.bmp"},
    {L"Damage_Red_Cri_8", L"Texture\\UI\\Damage\\Critical\\0.effect.NoCri1.8.bmp"},
    {L"Damage_Red_Cri_9", L"Texture\\UI\\Damage\\Critical\\0.effect.NoCri1.9.bmp"},
    {L"Damage_Red_Cri_man", L"Texture\\UI\\Damage\\Critical\\208.effect.NoCustom.NoCri1.3.bmp"},
    {L"Damage_Red_Cri_eok", L"Texture\\UI\\Damage\\Critical\\208.effect.NoCustom.NoCri1.4.bmp"},


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

    for (auto pair : g_TextureSource)
    {
        const wstring& strKey = pair.first;
        const wstring& strRelPath = pair.second;

        CTexture* pTexture = new CTexture;

        pTexture->SetKey(strKey);
        pTexture->SetRelativePath(strRelPath);

        wstring strAssetPath = strBasetPath + strRelPath;
        pTexture->Load(strAssetPath);

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
