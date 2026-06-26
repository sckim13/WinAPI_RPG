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
    //for (auto& pair : m_mapTexture)
    //{
    //    Safe_Delete(pair.second);
    //}
    //m_mapTexture.clear();
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
