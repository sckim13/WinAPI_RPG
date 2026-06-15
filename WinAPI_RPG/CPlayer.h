#pragma once
#include "CCharacter.h"

class CTexture;

class CPlayer : public CCharacter
{

public:
	CPlayer();
	~CPlayer();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;
	
	virtual void Render() override;

private:
	CTexture* m_pTexture;
};

