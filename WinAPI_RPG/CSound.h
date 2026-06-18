#pragma once

#include "CResource.h"

class CSound : public CResource
{
public:
	CSound();
	virtual ~CSound();

	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;
};

