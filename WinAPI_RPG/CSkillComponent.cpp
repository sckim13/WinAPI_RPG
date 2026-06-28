#include "pch.h"
#include "CSkillComponent.h"
#include "CSkill.h"
#include "CSceneManager.h"
#include "CHitScanSkill.h"

CSkillComponent::CSkillComponent()
{
}

CSkillComponent::~CSkillComponent()
{
}

void CSkillComponent::Initialize()
{
	m_vecSkill.push_back(L"ActiveSkill");
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
}

void CSkillComponent::Render(HDC hDC)
{
}

CActiveSkill* CSkillComponent::CreateSkill(const wstring& wstrName)
{
	Vec2 vPlayerPos = GetOwner()->GetPosition();

	CObject* pObject = CAbstractFactory<CObject, CHitScanSkill>::Create();
	CSceneManager::GetInstance()->RequestAddObject(pObject, EObjectType::SKILL);

	CSkill* pSkill = dynamic_cast<CSkill*>(pObject);
	if (pSkill)
	{
		pSkill->SetPosition(vPlayerPos);
		pSkill->Execute();
	}

	return dynamic_cast<CActiveSkill*>(pSkill);
}
