#include "pch.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CTexture.h"
#include "CPathManager.h"
#include "CMonster.h"
#include "CTransform.h"
#include "CCollider.h"

CScene::CScene(const wstring& wstr) : m_strName(wstr)
{
}

CScene::~CScene()
{
	Release();
}

void CScene::Initialize()
{
	CPlayer* pPlayer = new CPlayer;
	m_vecObject[(UINT)EObjectType::PLAYER].push_back(pPlayer);
	CMonster* pMonsterA = new CMonster;
	m_vecObject[(UINT)EObjectType::MONSTER].push_back(pMonsterA);

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
	
	for (auto& pPlayer : m_vecObject[(int)EObjectType::PLAYER])
	{
		for (auto& pMonster : m_vecObject[(int)EObjectType::MONSTER])
		{
			UINT64 ID = GetPairID(pPlayer->GetCollider(), pMonster->GetCollider());
			auto iter = m_mapPrevCollisionInfo.find(ID);
			if (IsColliding(pPlayer, pMonster))
			{
				if ((iter == m_mapPrevCollisionInfo.end()) || (iter->second == false))
				{
					cout << "Collision Start" << endl;
					pPlayer->GetCollider()->OnCollisionBegin(pMonster->GetCollider());
					pMonster->GetCollider()->OnCollisionBegin(pPlayer->GetCollider());
				}
				else
				{
					pPlayer->GetCollider()->OnCollision(pMonster->GetCollider());
					pMonster->GetCollider()->OnCollision(pPlayer->GetCollider());
				}
				m_mapPrevCollisionInfo[ID] = true;
			}
			else
			{
				if ((iter != m_mapPrevCollisionInfo.end()) && (iter->second == true))
				{
					cout << "Collision End" << endl;
					pPlayer->GetCollider()->OnCollisionEnd(pMonster->GetCollider());
					pMonster->GetCollider()->OnCollisionEnd(pPlayer->GetCollider());
				}
				m_mapPrevCollisionInfo[ID] = false;
			}
		}
	}

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

bool CScene::IsColliding(CObject* lhs, CObject* rhs)
{
	RECT* rclhs = lhs->GetCollider()->GetRect();
	RECT* rcrhs = rhs->GetCollider()->GetRect();

	RECT rcRes;
	return IntersectRect(&rcRes, rclhs, rcrhs);
}

UINT64 CScene::GetPairID(CCollider* lhs, CCollider* rhs)
{
	UINT32 l = lhs->GetID();
	UINT32 r = rhs->GetID();
	if (l > r) swap(l, r);
	return ((UINT64)l << 32) | (UINT64)r;
}
