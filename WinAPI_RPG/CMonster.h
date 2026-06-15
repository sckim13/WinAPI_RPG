#pragma once
#include "CCharacter.h"
class CMonster : public CCharacter
{
public:
	CMonster();
	virtual ~CMonster();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	virtual void Render() override;

private:
};

