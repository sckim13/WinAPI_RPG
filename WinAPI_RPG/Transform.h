#pragma once

#include "Mat3.h"
#include "Vec2.h"

typedef struct tagTransform
{
public:
	tagTransform() : m_vPosition(Vec2{}), m_fRotation(0.f)
	{
	}

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
	inline void SetScale(Vec2 vScale) { m_vScale= vScale; }
} TRANSFORM;