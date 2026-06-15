#pragma once

class CCollider;
class CTransform;
class CTexture;

class CObject
{
public:
	CObject();
	virtual ~CObject();

	virtual void Initialize();
	virtual void Update();
	virtual void Release();

	virtual void Render(HDC hDC) PURE;



protected:
	Vec2 m_vPosition;
	float m_fRotation;
	Vec2 m_vScale;

	CObject* m_pOwner;
	CTransform* m_pTransform;
	CTexture* m_pTexture;
	CCollider* m_pCollider;

private:

public:
	inline Vec2 GetPosition() { return m_vPosition; }
	inline float GetRotation() { return m_fRotation; }
	inline Vec2 GetScale() { return m_vScale; }

	inline void SetPosition(Vec2 Position) { m_vPosition = Position; }
	inline void SetPosition(float Rotation) { m_fRotation = Rotation; }
	inline void SetScale(Vec2 Scale) { m_vScale = Scale; }

	inline void SetOwner(CObject* pObject) { m_pOwner = pObject; }

};

