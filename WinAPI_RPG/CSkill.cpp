#include "pch.h"
#include "CSkill.h"
#include "CResourceManager.h"

CSkill::CSkill()
{
	m_eObjectType = EObjectType::SKILL;
}

CSkill::~CSkill()
{
}

void CSkill::Initialize()
{
	__super::Initialize();

}

void CSkill::PostInitialize()
{
	__super::PostInitialize();
}

void CSkill::Update()
{
	__super::Update();
}

void CSkill::LateUpdate()
{
	__super::LateUpdate();
}

void CSkill::Release()
{
}

void CSkill::Render(HDC hDC)
{
}
