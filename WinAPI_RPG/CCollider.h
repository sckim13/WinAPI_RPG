#pragma once

#include "CObjectBase.h"

class CCollider : public CObjectBase
{
public:
	CCollider();
	virtual ~CCollider();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	virtual void Render(HDC hDC) override;

private:
	//void OnCollisionBegin();
	//void OnCollision();
	//void OnCollisionEnd();
};

