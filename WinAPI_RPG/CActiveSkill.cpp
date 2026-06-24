#include "pch.h"
#include "CActiveSkill.h"
#include "CCollider.h"
#include "CMonster.h"

CActiveSkill::CActiveSkill()
{
}

CActiveSkill::~CActiveSkill()
{
}

void CActiveSkill::Initialize()
{
	__super::Initialize();

	m_pTexture = CResourceManager::GetInstance()->LoadTexture(L"Player", L"Texture\\Player.bmp");
	m_pTexture->SetOwner(this);
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

void CActiveSkill::OnCollisionBegin(TCollisionCtx Ctx)
{
	auto [pCollider] = Ctx;

	CObject* pObject = pCollider->GetOwner();
	if ()
	{

	}
}

void CActiveSkill::OnCollision(TCollisionCtx Ctx)
{
}

void CActiveSkill::OnCollisionEnd(TCollisionCtx Ctx)
{
}
