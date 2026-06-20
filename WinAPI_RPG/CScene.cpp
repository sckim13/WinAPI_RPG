#include "pch.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CTexture.h"
#include "CPathManager.h"
#include "CMonster.h"
#include "CTransform.h"
#include "CCollider.h"
#include "CEquipItem.h"

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
	
	CheckCollisionGroup(EObjectType::MONSTER, EObjectType::PLAYER);
	CheckCollisionGroup(EObjectType::ITEM, EObjectType::PLAYER);

	for (int i = 0; i < (int)EObjectType::MAX; ++i)
	{
		for (auto& pObject : m_vecObject[i])
		{
			pObject->LateUpdate();
		}
	}
}

void CScene::CheckCollisionGroup(EObjectType lGroup, EObjectType rGroup)
{
	for (auto& plObject : m_vecObject[(int)lGroup])
	{
		for (auto& prObject : m_vecObject[(int)rGroup])
		{
			UINT64 ID = GetPairID(plObject->GetCollider(), prObject->GetCollider());
			auto iter = m_mapPrevCollisionInfo.find(ID);
			if (IsColliding(plObject, prObject))
			{
				if ((iter == m_mapPrevCollisionInfo.end()) || (iter->second == false))
				{
					wcout << "[Collision Manager] Collision Start : " << plObject->GetName() << " & " << prObject->GetName() << endl;
					plObject->GetCollider()->OnCollisionBegin(prObject->GetCollider());
					prObject->GetCollider()->OnCollisionBegin(plObject->GetCollider());
				}
				else
				{
					plObject->GetCollider()->OnCollision(prObject->GetCollider());
					prObject->GetCollider()->OnCollision(plObject->GetCollider());
				}
				m_mapPrevCollisionInfo[ID] = true;
			}
			else
			{
				if ((iter != m_mapPrevCollisionInfo.end()) && (iter->second == true))
				{
					wcout << "[Collision Manager] Collision End : " << plObject->GetName() << " & " << prObject->GetName() << endl;
					plObject->GetCollider()->OnCollisionEnd(prObject->GetCollider());
					prObject->GetCollider()->OnCollisionEnd(plObject->GetCollider());
				}
				m_mapPrevCollisionInfo[ID] = false;
			}
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
	if (!lhs->GetCollider()->IsEnabled() || !rhs->GetCollider()->IsEnabled()) return false;
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
