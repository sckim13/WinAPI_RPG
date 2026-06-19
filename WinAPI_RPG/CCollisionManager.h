#pragma once

#include "CManager.h"

class CCollisionManager : public CManager
{
	SINGLETON(CCollisionManager);

public:
	void Initialize() override;
	void PostInitialize() override;
	void Update() override;
	void LateUpdate() override;
	void Release() override;
	void Render(HDC hDC) override;

};

