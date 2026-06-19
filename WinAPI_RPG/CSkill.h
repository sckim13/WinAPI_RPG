#pragma once

#include "CObject.h"

class CCollider;

class CSkill : public CObject
{
public:
	CSkill();
	virtual ~CSkill();

	void Initialize() override;
	void PostInitialize() override;
	void Update() override;
	void LateUpdate() override;
	void Release() override;
	void Render(HDC hDC) override;

private:
	CTexture* m_pTexture;
	CCollider* m_pCollider;

	/* Skill Info */

	ESkillType m_eSkillType;

	int m_iLevel;
	int m_iMaxLevel;
	
	bool m_bOnOff;
};

