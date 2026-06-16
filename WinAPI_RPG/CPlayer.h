#pragma once
#include "CCharacter.h"

class CTexture;

class CPlayer : public CCharacter
{

public:
	CPlayer();
	virtual ~CPlayer();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;
	
	virtual void Render(HDC hDC) override;

private:

};

