#pragma once

class CObject;

class CCollider
{
public:
	virtual void Initialize();
	virtual void Update();
	virtual void Release();

	virtual void Render();


	inline void SetOwner(CObject* pObject) { m_pOwner = pObject; }
	inline CObject* GetOwner() { return m_pOwner; }

private:
	CObject* m_pOwner;

	Vec2 m_Pos;
	Vec2 m_Scale;

	//void OnCollisionBegin();
	//void OnCollision();
	//void OnCollisionEnd();
};

