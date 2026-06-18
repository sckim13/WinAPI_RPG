#pragma once

#include "CComponent.h"

class CTransform : public CComponent
{
public:
	CTransform();
	virtual ~CTransform();

	void Initialize() override;
	void PostInitialize() override;
	void Update() override;
	void LateUpdate() override;
	void Release() override;
	void Render(HDC hDC) override;

private:
	// Mat3 m_mTransform;
	Vec2 m_vPosition;
	float m_fRotation;
	Vec2 m_vScale;

public:
	inline Vec2 GetPosition() { return m_vPosition; }
	inline float GetRotation() { return m_fRotation; }
	inline Vec2 GetScale() { return m_vScale; }
	inline void SetPosition(Vec2 vPos) { m_vPosition = vPos; }
	inline void SetRotation(float fRot) { m_fRotation = fRot; }
	inline void SetScale(Vec2 vScale) { m_vScale = vScale; }


};

