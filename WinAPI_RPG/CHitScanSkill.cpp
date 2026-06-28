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
	__super::Initialize();

	m_pAnimator->BindTexture(L"ActiveSkill");
	
	m_pCollider = new CCollider;
	m_pCollider->AttachTo(this);
	m_pCollider->SetSize(m_pAnimator->GetFrameSize());
	m_pCollider->SetEnabled(false);
}

void CHitScanSkill::PostInitialize()
{
	__super::PostInitialize();

	m_pCollider->m_OnCollisionBegin->AddBinding(GetID(), [this](const TCollisionCtx& Ctx) { OnCollisionBegin(Ctx); });
	m_pCollider->m_OnCollisionEnd->AddBinding(GetID(), [this](const TCollisionCtx& Ctx) { OnCollisionEnd(Ctx); });

	m_pAnimator->m_OnFinished->AddBinding(GetID(), [this]() { OnAnimationFinished(); });
}

void CHitScanSkill::Update()
{
	__super::Update();

	if (m_pAnimator->GetCurrentFrame() == m_iHitScanFrame)
	{
		m_pCollider->SetEnabled(true);
	}
	else
	{
		m_pCollider->SetEnabled(false);
	}
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
		CCombatManager::GetInstance()->RequestDamage(pMonster, vector<long long>{1000, 1001, 1002, 1003});
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
