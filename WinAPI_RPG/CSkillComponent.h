#pragma once

#include "CComponent.h"

class CSkill;

class CSkillComponent : public CComponent
{
public:
	CSkillComponent();
	virtual ~CSkillComponent();

	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	void AddSkill(const wstring& wstrName, CSkill* pSkill);

private:
	map<const wstring, CSkill*> m_mapSkill;

public:
	CSkill* GetSkillByName(const wstring& wstrName) { return m_mapSkill[wstrName]; }
};

