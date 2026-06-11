#pragma once

class CObject
{
public:
	CObject();
	~CObject();

public:

	inline Vec2 GetPosition() { return m_vPosition; }
	inline Vec2 GetScale() { return m_vScale; }

	inline void SetPosition(Vec2 Position) { m_vPosition = Position; }
	inline void SetScale(Vec2 Scale) { m_vScale = Scale; }

private:
	Vec2 m_vPosition;
	Vec2 m_vScale;
};

