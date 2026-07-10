#include "pch.h"
#include "CSceneManager.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"
#include "Struct.h"

vector<TSceneInfo> g_vecScene =
{
	TSceneInfo{L"TempMap", L"map_background1", L"map_front1"},
};

CSceneManager::CSceneManager() : m_pCurrentScene(nullptr)
{
}

CSceneManager::~CSceneManager()
{
	Release();
}

void CSceneManager::Initialize()
{
	// Caution : Player does not initialized by scene itself
	m_pPlayer = new CPlayer;
	m_pPlayer->Initialize();

	for (auto& Format : g_vecScene)
	{
		auto [wstrName, wstrBackKey, wstrFrontKey] = Format;
		CScene* pScene = new CScene(wstrName, wstrBackKey, wstrFrontKey);
		pScene->Initialize();
		m_mapScene.insert({wstrName, pScene});
	}

	m_pCurrentScene = m_mapScene[L"TempMap"];
}

void CSceneManager::PostInitialize()
{
	m_pCurrentScene->PostInitialize();
	m_pPlayer->PostInitialize();
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

void CSceneManager::AddObject(CObject* pObject, EObjectType eType)
{
	m_pCurrentScene->AddObject(pObject, eType);
}

void CSceneManager::RequestAddObject(CObject* pObject, EObjectType eType)
{
	m_pCurrentScene->RequestAddObject(pObject, eType);
}

inline list<CObject*>* CSceneManager::GetObjectList(EObjectType eType)
{
	return m_pCurrentScene->GetObjectList(eType);
}
