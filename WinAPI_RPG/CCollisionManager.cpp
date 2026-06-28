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

void CCollisionManager::CheckCollisionGroup(list<CObject*>& lGroup, list<CObject*>& rGroup)
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
					/* normal collision case */
					wcout << "[Collision Manager] Collision Start : " << plObject->GetName() << " & " << prObject->GetName() << endl;
					plObject->GetCollider()->OnCollisionBegin(TCollisionCtx{ prObject->GetCollider() });
					prObject->GetCollider()->OnCollisionBegin(TCollisionCtx{ plObject->GetCollider() });
					m_mapPrevCollisionInfo.insert_or_assign(ID, true);
				}
				else
				{
					if (plObject->IsDead() || prObject->IsDead())
					{
						/* end collision when one or more object is pending dead */
						wcout << "[Collision Manager] Collision End : " << plObject->GetName() << " & " << prObject->GetName() << endl;
						plObject->GetCollider()->OnCollisionEnd(TCollisionCtx{ prObject->GetCollider() });
						prObject->GetCollider()->OnCollisionEnd(TCollisionCtx{ plObject->GetCollider() });
						m_mapPrevCollisionInfo[ID] = false;
					}
					else
					{
						/* normal collision case */
						plObject->GetCollider()->OnCollision(TCollisionCtx{ prObject->GetCollider() });
						prObject->GetCollider()->OnCollision(TCollisionCtx{ plObject->GetCollider() });
						m_mapPrevCollisionInfo.insert_or_assign(ID, true);
					}
				}
			}
			else
			{
				if ((iter != m_mapPrevCollisionInfo.end()) && (iter->second == true))
				{
					wcout << "[Collision Manager] Collision End : " << plObject->GetName() << " & " << prObject->GetName() << endl;
					plObject->GetCollider()->OnCollisionEnd(TCollisionCtx{ prObject->GetCollider() });
					prObject->GetCollider()->OnCollisionEnd(TCollisionCtx{ plObject->GetCollider() });
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
