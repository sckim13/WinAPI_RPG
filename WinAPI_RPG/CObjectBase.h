#pragma once

class CCollider;
class CTransform;
class CTexture;

class CObjectBase
{
public:
	CObjectBase();
	virtual ~CObjectBase();

	virtual void Initialize() PURE;
	virtual void Update() PURE;
	virtual void Release() PURE;

	virtual void Render(HDC hDC);

protected:
	CObjectBase* m_pOwner;

	//Vec2 m_vPosition;
	//float m_fRotation;
	//Vec2 m_vScale;
private:

public:
	//inline Vec2 GetPosition() { return m_vPosition; }
	//inline float GetRotation() { return m_fRotation; }
	//inline Vec2 GetScale() { return m_vScale; }

	//inline void SetPosition(Vec2 Position) { m_vPosition = Position; }
	//inline void SetPosition(float Rotation) { m_fRotation = Rotation; }
	//inline void SetScale(Vec2 Scale) { m_vScale = Scale; }

	inline void SetOwner(CObjectBase* pObject) { m_pOwner = pObject; }

};

