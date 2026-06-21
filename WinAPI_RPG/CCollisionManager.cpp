#include "pch.h"
#include "CCollisionManager.h"
#include "CCollider.h"
#include "CObject.h"

CCollisionManager::CCollisionManager()
{
}

CCollisionManager::~CCollisionManager()
{
}

void CCollisionManager::Initialize()
{
}

void CCollisionManager::PostInitialize()
{
}

void CCollisionManager::Update()
{
}

void CCollisionManager::LateUpdate()
{
}

void CCollisionManager::Release()
{
}

void CCollisionManager::Render(HDC hDC)
{
}

void CCollisionManager::CheckCollisionGroup(vector<CObject*>& lGroup, vector<CObject*>& rGroup)
{
	for (auto& plObject : lGroup)
	{
		for (auto& prObject : rGroup)
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

bool CCollisionManager::IsColliding(CObject* lhs, CObject* rhs)
{
	if (!lhs->GetCollider()->IsEnabled() || !rhs->GetCollider()->IsEnabled()) return false;
	RECT* rclhs = lhs->GetCollider()->GetRect();
	RECT* rcrhs = rhs->GetCollider()->GetRect();

	RECT rcRes;
	return IntersectRect(&rcRes, rclhs, rcrhs);
}

UINT64 CCollisionManager::GetPairID(CCollider* lhs, CCollider* rhs)
{
	UINT32 l = lhs->GetID();
	UINT32 r = rhs->GetID();
	if (l > r) swap(l, r);
	return ((UINT64)l << 32) | (UINT64)r;
}
