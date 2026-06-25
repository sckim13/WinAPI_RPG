#include "pch.h"
#include "CSceneManager.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"

CSceneManager::CSceneManager() : m_pCurrentScene(nullptr)
{
}

CSceneManager::~CSceneManager()
{
	Release();
}

void CSceneManager::Initialize()
{
	m_pPlayer = new CPlayer;

	// later heap allocation on array instead of direct heap allocation
	m_pCurrentScene = new CScene(L"TempMap");
	m_pCurrentScene->Initialize(m_pPlayer);
}

void CSceneManager::PostInitialize()
{
	m_pCurrentScene->PostInitialize();
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
	Safe_Delete<CScene*>(m_pCurrentScene);
}

void CSceneManager::Render(HDC hDC)
{
	m_pCurrentScene->Render(hDC);
}