#pragma once
#include "CObject.h"

class CCharacter : public CObject
{
public:
	CCharacter();
	virtual ~CCharacter();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	virtual void Render() override;

private:
};

