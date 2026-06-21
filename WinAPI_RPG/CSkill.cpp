#include "pch.h"
#include "CSkill.h"
#include "CResourceManager.h"

CSkill::CSkill()
{
}

CSkill::~CSkill()
{
}

void CSkill::Initialize()
{
	__super::Initialize();

	m_eObjectType = EObjectType::SKILL;
}

void CSkill::PostInitialize()
{
}

void CSkill::Update()
{
}

void CSkill::LateUpdate()
{
}

void CSkill::Release()
{
}

void CSkill::Render(HDC hDC)
{
}
