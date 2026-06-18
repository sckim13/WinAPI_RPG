#pragma once
#include "CObject.h"

class CTexture;
class CCollider;
class CTransform;

class CCharacter : public CObject
{
public:
	CCharacter();
	virtual ~CCharacter() PURE;

	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

protected:
	EPoseDirection m_ePoseDir;


private:
};

