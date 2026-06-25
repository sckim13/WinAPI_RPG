#pragma once

#include "CBase.h"

class CTexture;
class CCollider;
class CComponent;

class CObject : public CBase
{
public:
	CObject();
	virtual ~CObject() PURE;

	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) PURE;

	void AddComponent(CComponent* pComponent);

protected:
	CTexture* m_pTexture;
	CCollider* m_pCollider;
	EObjectType m_eObjectType;
	wstring m_wstrName;
	vector<CComponent*> m_vecComponent;

	virtual void OnKeyEventTriggered(TKeyEventCtx Ctx);

public:
	inline CTexture* GetTexture() const { return m_pTexture; }
	inline CCollider* GetCollider() const { return m_pCollider; }
	inline EObjectType GetObjectType() const { return m_eObjectType; }
	inline const wstring GetName() const { return m_wstrName; }

	inline void SetName(wstring& wstrName) { m_wstrName = wstrName; }
};

