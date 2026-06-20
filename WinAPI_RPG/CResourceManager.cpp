#include "pch.h"
#include "CResourceManager.h"
#include "CPathManager.h"
#include "CTexture.h"

CResourceManager::CResourceManager()
{

}

CResourceManager::~CResourceManager()
{
    Release();
}

void CResourceManager::Initialize()
{
    /* TODO : Load All Texture on the Asset Here */
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

CTexture* CResourceManager::LoadTexture(const wstring& strKey, const wstring& strRelPath)
{
    CTexture* pTexture = FindTexture(strKey);
    if (pTexture)
    {
        return pTexture;
    }
 
    wstring strAssetPath = CPathManager::GetInstance()->GetBasePath();
    strAssetPath += strRelPath;

    /* TODO : assert when there is no Texture on the texture map */
    pTexture = new CTexture;
    pTexture->SetKey(strKey);
    pTexture->SetRelativePath(strRelPath);
    pTexture->Load(strAssetPath);

    m_mapTexture.insert({strKey, pTexture});

    return pTexture;
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
