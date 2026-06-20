#pragma once
#include "CObject.h"

class CTexture;
class CCollider;
class CTransform;
class CController;

class CCharacter : public CObject
{
public:
	CCharacter();
	virtual ~CCharacter() PURE;

	virtual void Initialize() override;
	virtual void PostInitialize() PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Release() PURE;
	virtual void Render(HDC hDC) PURE;

protected:
	EPoseDirection m_ePoseDir;

private:
	CController* m_pController;

public:
	inline void SetController(CController* pCtrl) { m_pController = pCtrl; }
	inline CController* GetController() { return m_pController; }
};

