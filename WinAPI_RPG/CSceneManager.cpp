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
	m_pCurrentScene = new CScene(L"TEmpMap");
}

void CSceneManager::Update()
{
	m_pCurrentScene->Update();
}

void CSceneManager::Render()
{
	m_pCurrentScene->Render();
}