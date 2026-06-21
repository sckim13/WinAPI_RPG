#pragma once

#include "CObject.h"

class CCollider;

class CSkill : public CObject
{
public:
	CSkill();
	virtual ~CSkill();

	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	virtual void Execute() PURE;

private:
	/* Skill Info */

	ESkillType m_eSkillType;

	int m_iLevel;
	int m_iMaxLevel;

};

