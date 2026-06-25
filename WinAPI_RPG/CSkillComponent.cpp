#include "pch.h"
#include "CSkillComponent.h"
#include "CSkill.h"

CSkillComponent::CSkillComponent()
{
}

CSkillComponent::~CSkillComponent()
{
}

void CSkillComponent::Initialize()
{
}

void CSkillComponent::PostInitialize()
{
}

void CSkillComponent::Update()
{
}

void CSkillComponent::LateUpdate()
{
}

void CSkillComponent::Release()
{
	for (auto pair : m_mapSkill)
	{
		Safe_Delete<CSkill*>(pair.second);
	}
}

void CSkillComponent::Render(HDC hDC)
{
}

void CSkillComponent::AddSkill(const wstring& wstrName, CSkill* pSkill)
{
	m_mapSkill.insert({ wstrName, pSkill });
}
