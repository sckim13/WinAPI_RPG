#pragma once

#include "CObject.h"

class CFootHold : public CObject
{
public:
	CFootHold();
	virtual ~CFootHold();

	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

private:
	Vec2 m_vLeft;
	Vec2 m_vRight;

	CFootHold* m_Left;
	CFootHold* m_Right;

	int m_iLayer;
};

