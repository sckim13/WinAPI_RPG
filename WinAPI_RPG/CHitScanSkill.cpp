#include "pch.h"
#include "CHitScanSkill.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CResourceManager.h"
#include "CAnimator.h"

CHitScanSkill::CHitScanSkill()
{
}

CHitScanSkill::~CHitScanSkill()
{
	Release();
}

void CHitScanSkill::Initialize()
{
	__super::Initialize();

	m_pCollider = new CCollider;
	m_pCollider->AttachTo(this);

	CResourceManager::GetInstance()->LoadTexture(L"ActiveSkill");
	m_pAnimator = new CAnimator;
	m_pAnimator->AttachTo(this);
	m_pAnimator->BindTexture(L"ActiveSkill");
}

void CHitScanSkill::PostInitialize()
{
	__super::PostInitialize();

	m_pCollider->m_OnCollisionBegin->AddBinding(GetID(), [this](const TCollisionCtx& Ctx) { OnCollisionBegin(Ctx); });
	m_pCollider->m_OnCollisionEnd->AddBinding(GetID(), [this](const TCollisionCtx& Ctx) { OnCollisionEnd(Ctx); });
}

void CHitScanSkill::Update()
{
	__super::Update();
}

void CHitScanSkill::LateUpdate()
{
	__super::LateUpdate();
}

void CHitScanSkill::Release()
{
}

void CHitScanSkill::Render(HDC hDC)
{
	m_pAnimator->Render(hDC);
}

void CHitScanSkill::Execute()
{
	cout << "[HitScanSkill] Execute" << endl;

	/* animator play animation */
	m_pAnimator->Play();
	/* set collision enabled 1Frame */
	m_pCollider->SetEnabled(true);
	/* */
}

void CHitScanSkill::OnCollisionBegin(const TCollisionCtx& Ctx)
{
	__super::OnCollisionBegin(Ctx);

	auto [pCollider] = Ctx;

	CObject* pObject = pCollider->GetOwner();

	if (CMonster* pMonster = dynamic_cast<CMonster*>(pObject))
	{
		pMonster->OnHit();
	}
}

void CHitScanSkill::OnCollision(const TCollisionCtx& Ctx)
{
}

void CHitScanSkill::OnCollisionEnd(const TCollisionCtx& Ctx)
{
}
