#pragma once

#include "CManager.h"

class CObject;
class CCollider;

class CCollisionManager : public CManager
{
	SINGLETON(CCollisionManager);

public:
	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	void CheckCollisionGroup(vector<CObject*>& lGroup, vector<CObject*>& rGroup);

private:
	bool IsColliding(CObject* lhs, CObject* rhs);
	UINT64 GetPairID(CCollider* lhs, CCollider* rhs);

	map<UINT64, bool> m_mapPrevCollisionInfo;
};

