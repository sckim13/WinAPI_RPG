#include "pch.h"
#include "CSceneManager.h"
#include "CScene.h"

CSceneManager::CSceneManager() : m_pCurrentScene(nullptr)
{
}

CSceneManager::~CSceneManager()
{
	Safe_Delete(m_pCurrentScene);
}

void CSceneManager::Initialize()
{
	// later heap allocation on array instead of direct heap allocation
	m_pCurrentScene = new CScene(L"TempMap");
	m_pCurrentScene->Initialize();
}

void CSceneManager::PostInitialize()
{
}

void CSceneManager::Update()
{
	m_pCurrentScene->Update();
}

void CSceneManager::LateUpdate()
{
	m_pCurrentScene->LateUpdate();
}

void CSceneManager::Release()
{
}

void CSceneManager::Render(HDC hDC)
{
	m_pCurrentScene->Render(hDC);
}