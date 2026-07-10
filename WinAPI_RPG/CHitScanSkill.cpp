#include "pch.h"
#include "CHitScanSkill.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CResourceManager.h"
#include "CAnimator.h"
#include "CCombatManager.h"

CHitScanSkill::CHitScanSkill() : m_iHitScanFrame()
{
}

CHitScanSkill::~CHitScanSkill()
{
	Release();
}

void CHitScanSkill::Initialize()
{
	m_pAnimator = new CAnimator;
	m_pAnimator->AttachTo(this);
	m_pAnimator->BindTexture(L"ActiveSkill");
	
	m_pCollider = new CCollider;
	m_pCollider->AttachTo(this);
	m_pCollider->SetSize(m_pAnimator->GetFrameSize());
	m_pCollider->SetEnabled(false);

	__super::Initialize();
}

void CHitScanSkill::PostInitialize()
{
	m_pCollider->m_OnCollisionBegin->AddBinding(GetID(), [this](const TCollisionCtx& Ctx) { OnCollisionBegin(Ctx); });
	m_pCollider->m_OnCollisionEnd->AddBinding(GetID(), [this](const TCollisionCtx& Ctx) { OnCollisionEnd(Ctx); });

	m_pAnimator->m_OnFinished->AddBinding(GetID(), [this]() { OnAnimationFinished(); });

	__super::PostInitialize();
}

void CHitScanSkill::Update()
{
	if (m_pAnimator->GetCurrentFrame() == m_iHitScanFrame)
	{
		m_pCollider->SetEnabled(true);
	}
	else
	{
		m_pCollider->SetEnabled(false);
	}

	__super::Update();
}

void CHitScanSkill::LateUpdate()
{
	__super::LateUpdate();
}

void CHitScanSkill::Release()
{
	m_pCollider->m_OnCollisionBegin->DeleteBinding(GetID());
	m_pCollider->m_OnCollisionEnd->DeleteBinding(GetID());

	m_pAnimator->m_OnFinished->DeleteBinding(GetID());
}

void CHitScanSkill::Render(HDC hDC)
{
	m_pAnimator->Render(hDC);
	m_pCollider->Render(hDC);
}

void CHitScanSkill::Execute()
{
	m_pAnimator->Play(false);
}

void CHitScanSkill::OnCollisionBegin(const TCollisionCtx& Ctx)
{
	__super::OnCollisionBegin(Ctx);

	auto [pCollider] = Ctx;

	CObject* pObject = pCollider->GetOwner();

	if (CMonster* pMonster = dynamic_cast<CMonster*>(pObject))
	{
		CCombatManager::GetInstance()->RequestDamage(pMonster, vector<long long>{12345678, 123456789, 9876543210, 1234567890});
	}
}

void CHitScanSkill::OnCollision(const TCollisionCtx& Ctx)
{
}

void CHitScanSkill::OnCollisionEnd(const TCollisionCtx& Ctx)
{
}

void CHitScanSkill::OnAnimationFinished()
{
	SetDead();
}
