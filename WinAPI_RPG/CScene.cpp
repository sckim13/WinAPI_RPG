#include "pch.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CTexture.h"
#include "CPathManager.h"
#include "CMonster.h"
#include "CTransform.h"
#include "CCollider.h"
#include "CEquipItem.h"
#include "CCollisionManager.h"
#include "CTextureComponent.h"
#include "CSceneManager.h"

CScene::CScene(const wstring& wstrName, const wstring& wstrBackKey, const wstring& wstrFrontKey)
	: m_wstrName(wstrName), m_wstrBackKey(wstrBackKey), m_wstrFrontKey(wstrFrontKey)
{
}

CScene::~CScene()
{
	Release();
}

void CScene::Initialize()
{
	// Map Texture Maching
	m_pTextureFront = new CTextureComponent;
	m_pTextureFront->Initialize();
	m_pTextureFront->BindTexture(m_wstrFrontKey);
	m_pTextureBack = new CTextureComponent;
	m_pTextureBack->Initialize();
	m_pTextureBack->BindTexture(m_wstrBackKey);

	// TOOD : for testing
	CObject* pPlayer = CSceneManager::GetInstance()->GetPlayer();
	m_listObject[(UINT)EObjectType::PLAYER].push_back(pPlayer);
	CObject* pMonsterA = new CMonster;
	m_listObject[(UINT)EObjectType::MONSTER].push_back(pMonsterA);
	CObject* pItemA = new CEquipItem;
	m_listObject[(UINT)EObjectType::ITEM].push_back(pItemA);

	for (int i = 0; i < (int)EObjectType::MAX; ++i)
	{
		// exceptinon : skip player init
		if (i == (int)EObjectType::PLAYER) continue;
		
		for (auto& pObject : m_listObject[i])
		{
			pObject->Initialize();
		}
	}

	pPlayer->GetTransform()->SetPosition(Vec2{ 400, 300 });
	pPlayer->GetTransform()->SetScale(Vec2{ 100, 100 });

	pMonsterA->GetTransform()->SetPosition(Vec2{ 500, 300 });
	pMonsterA->GetTransform()->SetScale(Vec2{ 70, 70 });

	pItemA->GetTransform()->SetPosition(Vec2{ 300, 300 });
	pItemA->GetTransform()->SetScale(Vec2{ 10, 10 });
	//
}

void CScene::PostInitialize()
{
	for (int i = 0; i < (int)EObjectType::MAX; ++i)
	{
		if (i == (int)EObjectType::PLAYER) continue;

		for (auto& pObject : m_listObject[i])
		{
			pObject->PostInitialize();
		}
	}
}

void CScene::Update()
{
	// push the objects requested to be created at the last frame
	for (int i = 0; i < (int)EObjectType::MAX; ++i)
	{
		while (!m_queueObjectCreationRequested[i].empty())
		{
			CObject* pObject = m_queueObjectCreationRequested[i].front();
			m_listObject[i].push_back(pObject);
			m_queueObjectCreationRequested[i].pop();
		}
	}

	// normal object 
	for (int i = 0; i < (int)EObjectType::MAX; ++i)
	{
		for (auto iter = m_listObject[i].begin(); iter != m_listObject[i].end(); )
		{
			CObject* pObject = (*iter);
			if (pObject->IsDead())
			{
				Safe_Delete<CObject*>(pObject);
				iter = m_listObject[i].erase(iter);
			}
			else
			{
				pObject->Update();
				++iter;
			}
		}
	}
}

void CScene::LateUpdate()
{
	for (int i = 0; i < (int)EObjectType::MAX; ++i)
	{
		for (auto& pObject : m_listObject[i])
		{
			pObject->LateUpdate();
		}
	}

	/* check collision */
	CCollisionManager::GetInstance()->CheckCollisionGroup(m_listObject[(int)EObjectType::MONSTER], m_listObject[(int)EObjectType::PLAYER]);
	CCollisionManager::GetInstance()->CheckCollisionGroup(m_listObject[(int)EObjectType::ITEM], m_listObject[(int)EObjectType::PLAYER]);
	CCollisionManager::GetInstance()->CheckCollisionGroup(m_listObject[(int)EObjectType::SKILL], m_listObject[(int)EObjectType::MONSTER]);

}

void CScene::Release()
{
	for (int i = 0; i < (int)EObjectType::MAX; ++i)
	{
		for (auto& pObject : m_listObject[i])
		{
			Safe_Delete(pObject);
		}
	}

	// manual texturecomponent deleting
	Safe_Delete<CTextureComponent*>(m_pTextureBack);
	Safe_Delete<CTextureComponent*>(m_pTextureFront);
}

void CScene::Render(HDC hDC)
{
	m_pTextureBack->Render(hDC);
	m_pTextureFront->Render(hDC);

	for (int i = 0; i < (int)EObjectType::MAX; ++i)
	{
		for (auto& pObject : m_listObject[i])
		{
			pObject->Render(hDC);
		}
	}
}

void CScene::Enter()
{

}

void CScene::Exit()
{
	//for (int i = 0; i < (int)EObjectType::MAX; ++i)
	//{
	//	for (auto& pObject : m_listObject[i])
	//	{
	//		Safe_Delete(pObject);
	//	}
	//}

	// collisionmanager에게 이전 정보 초기화시키기
}

void CScene::AddObject(CObject* pObject, EObjectType eType)
{
	m_listObject[(int)eType].push_back(pObject);
}

void CScene::RequestAddObject(CObject* pObject, EObjectType eType)
{
	// initialize object manually since it is added in the middle of loop
	pObject->Initialize();
	pObject->PostInitialize();
	m_queueObjectCreationRequested[(int)eType].push(pObject);
}

IPoint CScene::GetMapSize()
{
	return m_pTextureFront->GetTextureSize();
}
