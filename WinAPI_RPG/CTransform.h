#pragma once

#include "CObject.h"

class CTransform : public CObject
{
public:
	CTransform();
	~CTransform();

	virtual void Initialize();
	virtual void Update();
	virtual void Release();

	virtual void Render();

private:
	// matrix for world coordinates TODO
	// Mat3 ...
	Vec2 m_vecPosition; // local
	float m_fRotation; // local

public:
	inline Vec2 GetPosition() { return m_vecPosition; }
	inline float GetRotation() { return m_fRotation; }
	inline void SetPosition(Vec2 vecPos) { m_vecPosition = vecPos; }
	inline void SetRotation(float fRot) { m_fRotation = fRot; }
};

