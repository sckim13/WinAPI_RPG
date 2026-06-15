#include "pch.h"
#include "CResourceManager.h"
#include "CPathManager.h"
#include "CTexture.h"

CResourceManager::CResourceManager()
{

}

CResourceManager::~CResourceManager()
{
    for (auto& pair : m_mapTexture)
    {
        Safe_Delete(pair.second);
    }
    m_mapTexture.clear();
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
