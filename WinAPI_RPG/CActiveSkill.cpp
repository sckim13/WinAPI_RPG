#include "pch.h"
#include "CActiveSkill.h"
#include "CCollider.h"
#include "CMonster.h"
#include "CResourceManager.h"
#include "CTextureComponent.h"

CActiveSkill::CActiveSkill() : m_pAnimator(nullptr)
{
}

CActiveSkill::~CActiveSkill()
{
}

void CActiveSkill::Initialize()
{
	__super::Initialize();

	m_pTextureComponent = new CTextureComponent;
	m_pTextureComponent->SetOwner(this);
	m_pTextureComponent->BindTexture(L"ActiveSkill");
}

void CActiveSkill::PostInitialize()
{
}

void CActiveSkill::Update()
{
}

void CActiveSkill::LateUpdate()
{
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
