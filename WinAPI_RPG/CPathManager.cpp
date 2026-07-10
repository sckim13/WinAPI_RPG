#include "pch.h"
#include "CPathManager.h"

namespace fs = std::filesystem;

CPathManager::CPathManager() : m_szBasePath{}
{
	Initialize();
}

CPathManager::~CPathManager()
{

}

void CPathManager::Initialize()
{
	GetCurrentDirectory(MAX_PATH_SIZE, m_szBasePath);
	
	fs::path AssetPath(m_szBasePath);
	AssetPath = AssetPath / L"Resource" / L"";
	
	wcscpy_s(m_szBasePath, AssetPath.c_str());
}

void CPathManager::PostInitialize()
{
}

void CPathManager::Update()
{
}

void CPathManager::LateUpdate()
{
}

void CPathManager::Release()
{
}

void CPathManager::Render(HDC hDC)
{
}
