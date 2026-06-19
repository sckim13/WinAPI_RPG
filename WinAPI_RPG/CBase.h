#pragma once

#include "CTransform.h"

class CBase
{
public:
	CBase();
	virtual ~CBase();

	virtual void Initialize() PURE;
	virtual void PostInitialize() PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Release() PURE;

	virtual void Render(HDC hDC) PURE;


protected:
	CTransform m_pTransform;

public:
	inline CTransform* GetTransform() { return &m_pTransform; }

	inline Vec2 GetPosition() { return GetTransform()->GetPosition(); }
	inline float GetRotation() { return GetTransform()->GetRotation(); }
	inline Vec2 GetScale() { return GetTransform()->GetScale(); }
	inline void SetPosition(Vec2 vPos) { return GetTransform()->SetPosition(vPos); }
	inline void SetRotation(float fRot) { return GetTransform()->SetRotation(fRot); }
	inline void SetScale(Vec2 vScale) { return GetTransform()->SetScale(vScale); }
};

