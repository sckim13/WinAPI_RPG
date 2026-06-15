#pragma once

#include "CObject.h"

class CCollider : public CObject
{
public:
	virtual void Initialize();
	virtual void Update();
	virtual void Release();

	virtual void Render();


	inline void SetOwner(CObject* pObject) { m_pOwner = pObject; }
	inline CObject* GetOwner() { return m_pOwner; }

private:
	//void OnCollisionBegin();
	//void OnCollision();
	//void OnCollisionEnd();
};

