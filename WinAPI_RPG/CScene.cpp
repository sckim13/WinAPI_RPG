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

CScene::CScene(const wstring& wstr) : m_strName(wstr)
{
}

CScene::~CScene()
{
	Release();
}

void CScene::Initialize()
{
	CObject* pPlayer = new CPlayer;
	m_listObject[(UINT)EObjectType::PLAYER].push_back(pPlayer);
	CObject* pMonsterA = new CMonster;
	m_listObject[(UINT)EObjectType::MONSTER].push_back(pMonsterA);
	CObject* pItemA = new CEquipItem;
	m_listObject[(UINT)EObjectType::ITEM].push_back(pItemA);

	for (int i = 0; i < (int)EObjectType::MAX; ++i)
	{
		for (auto& pObject : m_listObject[i])
		{
			pObject->Initialize();
		}
	}

	pPlayer->GetTransform()->SetPosition(Vec2{ 400, 300 });
	pPlayer->GetTransform()->SetScale(Vec2{ 100, 100 });

	pMonsterA->GetTransform()->SetPosition(Vec2{ 100, 100 });
	pMonsterA->GetTransform()->SetScale(Vec2{ 70, 70 });

	pItemA->GetTransform()->SetPosition(Vec2{ 200, 100 });
	pItemA->GetTransform()->SetScale(Vec2{ 10, 10 });
}

void CScene::Initialize(CPlayer* pPlayer)
{

	m_listObject[(UINT)EObjectType::PLAYER].push_back(pPlayer);
	CObject* pMonsterA = new CMonster;
	m_listObject[(UINT)EObjectType::MONSTER].push_back(pMonsterA);
	CObject* pItemA = new CEquipItem;
	m_listObject[(UINT)EObjectType::ITEM].push_back(pItemA);

	for (int i = 0; i < (int)EObjectType::MAX; ++i)
	{
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
}

void CScene::PostInitialize()
{
	for (int i = 0; i < (int)EObjectType::MAX; ++i)
	{
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
}

void CScene::Render(HDC hDC)
{
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
