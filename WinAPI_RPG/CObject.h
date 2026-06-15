#pragma once

class CCollider;

class CObject
{
public:
	CObject();
	~CObject();

	virtual void Initialize();
	virtual void Update();
	virtual void Release();

	virtual void Render();

public:

	inline Vec2 GetPosition() { return m_vPosition; }
	inline Vec2 GetScale() { return m_vScale; }

	inline void SetPosition(Vec2 Position) { m_vPosition = Position; }
	inline void SetScale(Vec2 Scale) { m_vScale = Scale; }

	void CreateCollider();

private:
	Vec2 m_vPosition;
	Vec2 m_vScale;

	CCollider* m_pCollider;
};

