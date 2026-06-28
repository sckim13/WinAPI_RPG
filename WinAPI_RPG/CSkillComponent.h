#pragma once

#include "CComponent.h"

class CActiveSkill;

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

	CActiveSkill* CreateSkill(const wstring& wstrName);

private:
	vector<wstring> m_vecSkill;

public:
};

