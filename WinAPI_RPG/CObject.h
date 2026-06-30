#pragma once

#include "CBase.h"
#include "CTransform.h"

class CTextureComponent;
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
	CTextureComponent* m_pTextureComponent;
	CCollider* m_pCollider;
	EObjectType m_eObjectType;
	wstring m_wstrName;
	bool m_bFlipped; // to flip texture
	vector<CComponent*> m_vecComponent;

	virtual void OnKeyEventTriggered(const TKeyEventCtx& Ctx);

	CTransform m_pTransform;

	bool m_bPendingDead;

public:
	inline CTransform* GetTransform() { return &m_pTransform; }

	inline Vec2 GetPosition() { return GetTransform()->GetPosition(); }
	inline float GetRotation() { return GetTransform()->GetRotation(); }
	inline Vec2 GetScale() { return GetTransform()->GetScale(); }
	inline void SetPosition(Vec2 vPos) { GetTransform()->SetPosition(vPos); }
	inline void SetRotation(float fRot) { GetTransform()->SetRotation(fRot); }
	inline void SetScale(Vec2 vScale) { GetTransform()->SetScale(vScale); }
	inline void SetDead() { m_bPendingDead = true; }
	inline void Flip(bool bFlip) { m_bFlipped = bFlip; }

	inline CTextureComponent* GetTextureComponent() const { return m_pTextureComponent; }
	inline CCollider* GetCollider() const { return m_pCollider; }
	inline EObjectType GetObjectType() const { return m_eObjectType; }
	inline const wstring& GetName() const { return m_wstrName; }
	inline bool IsFlipped() const { return m_bFlipped; }
	inline bool IsDead() const { return m_bPendingDead; }

	inline void SetName(wstring& wstrName) { m_wstrName = wstrName; }
};

