#pragma once

#include "CComponent.h"

class CMovementComponent : public CComponent
{
public:
	CMovementComponent();
	virtual ~CMovementComponent();

	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

private:
	float m_fMaxSpeed;

public:
	void SetMaxSpeed(float fSpeed) { m_fMaxSpeed = fSpeed; }

};

