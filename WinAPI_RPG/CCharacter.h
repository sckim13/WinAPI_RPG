#pragma once
#include "CObjectBase.h"

class CCharacter : public CObjectBase
{
public:
	CCharacter();
	virtual ~CCharacter();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	virtual void Render(HDC hDC) override;

	inline void SetPosition(Vec2 vPos) { m_Transform.SetPosition(vPos); }
	inline void SetRotation(float fRot) { m_Transform.SetRotation(fRot); }
	inline void SetScale(Vec2 vPos) { m_Transform.SetScale(vPos); }
	inline Vec2 GetPosition() { return m_Transform.GetPosition(); }
	inline float GetRotation() { return m_Transform.GetRotation(); }
	inline Vec2 GetScale() { return m_Transform.GetScale(); }

protected:
	CTexture* m_pTexture;
	TRANSFORM m_Transform;

private:
};

