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
	m_vecObject[(UINT)EObjectType::PLAYER].push_back(pPlayer);
	CObject* pMonsterA = new CMonster;
	m_vecObject[(UINT)EObjectType::MONSTER].push_back(pMonsterA);
	CObject* pItemA = new CEquipItem;
	m_vecObject[(UINT)EObjectType::ITEM].push_back(pItemA);

	for (int i = 0; i < (int)EObjectType::MAX; ++i)
	{
		for (auto& pObject : m_vecObject[i])
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
	m_vecObject[(UINT)EObjectType::PLAYER].push_back(pPlayer);
	CObject* pMonsterA = new CMonster;
	m_vecObject[(UINT)EObjectType::MONSTER].push_back(pMonsterA);
	CObject* pItemA = new CEquipItem;
	m_vecObject[(UINT)EObjectType::ITEM].push_back(pItemA);

	for (int i = 0; i < (int)EObjectType::MAX; ++i)
	{
		for (auto& pObject : m_vecObject[i])
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
}

void CScene::Update()
{
	for (int i = 0; i < (int)EObjectType::MAX; ++i)
	{
		for (auto& pObject : m_vecObject[i])
		{
			pObject->Update();
		}
	}
}

void CScene::LateUpdate()
{
	/* check collision */
	/* in toy case, compare Player and Monster */
	
	CCollisionManager::GetInstance()->CheckCollisionGroup(m_vecObject[(int)EObjectType::MONSTER], m_vecObject[(int)EObjectType::PLAYER]);
	CCollisionManager::GetInstance()->CheckCollisionGroup(m_vecObject[(int)EObjectType::ITEM], m_vecObject[(int)EObjectType::PLAYER]);
	CCollisionManager::GetInstance()->CheckCollisionGroup(m_vecObject[(int)EObjectType::SKILL], m_vecObject[(int)EObjectType::MONSTER]);

	for (int i = 0; i < (int)EObjectType::MAX; ++i)
	{
		for (auto& pObject : m_vecObject[i])
		{
			pObject->LateUpdate();
		}
	}
}

void CScene::Release()
{
	for (int i = 0; i < (int)EObjectType::MAX; ++i)
	{
		for (auto& pObject : m_vecObject[i])
		{
			Safe_Delete(pObject);
		}
	}
}

void CScene::Render(HDC hDC)
{
	for (int i = 0; i < (int)EObjectType::MAX; ++i)
	{
		for (auto& pObject : m_vecObject[i])
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
	//	for (auto& pObject : m_vecObject[i])
	//	{
	//		Safe_Delete(pObject);
	//	}
	//}
}