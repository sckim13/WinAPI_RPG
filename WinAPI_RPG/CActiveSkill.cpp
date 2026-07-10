#include "pch.h"
#include "CActiveSkill.h"
#include "CCollider.h"
#include "CMonster.h"
#include "CResourceManager.h"
#include "CTextureComponent.h"
#include "CAnimator.h"

CActiveSkill::CActiveSkill() : m_pAnimator(nullptr)
{
}

CActiveSkill::~CActiveSkill()
{
}

void CActiveSkill::Initialize()
{
	__super::Initialize();
}

void CActiveSkill::PostInitialize()
{
	__super::PostInitialize();
}

void CActiveSkill::Update()
{
	__super::Update();
}

void CActiveSkill::LateUpdate()
{
	__super::LateUpdate();
}

void CActiveSkill::Release()
{
}

void CActiveSkill::Render(HDC hDC)
{
}

void CActiveSkill::OnCollisionBegin(const TCollisionCtx& Ctx)
{
	auto [pCollider] = Ctx;

	CObject* pObject = pCollider->GetOwner();
	if (1)
	{

	}
}

void CActiveSkill::OnCollision(const TCollisionCtx& Ctx)
{
}

void CActiveSkill::OnCollisionEnd(const TCollisionCtx& Ctx)
{
}
