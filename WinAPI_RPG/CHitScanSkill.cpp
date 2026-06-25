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
}

void CHitScanSkill::Initialize()
{
	__super::Initialize();

	m_pCollider = new CCollider;
	m_pCollider->Initialize();

	m_pCollider->m_hOnCollisionBegin->AddBinding(this, [this](TCollisionCtx Ctx) { OnCollisionBegin(Ctx); });
	m_pCollider->m_hOnCollisionEnd->AddBinding(this, [this](TCollisionCtx Ctx) { OnCollisionEnd(Ctx); });

	CResourceManager::GetInstance()->LoadTexture(L"ActiveSkill", L"Texture\\ActiveSkill.bmp");
	m_pAnimator = new CAnimator;
	m_pAnimator->BindTexture(L"ActiveSkill");
	m_pAnimator->SetOwner(this);
}

void CHitScanSkill::PostInitialize()
{
}

void CHitScanSkill::Update()
{
	m_pAnimator->Update();
}

void CHitScanSkill::LateUpdate()
{
	SetPosition(GetPosition());
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

void CHitScanSkill::OnCollisionBegin(TCollisionCtx Ctx)
{
	__super::OnCollisionBegin(Ctx);

	auto [pCollider] = Ctx;

	CObject* pObject = pCollider->GetOwner();

	if (CMonster* pMonster = dynamic_cast<CMonster*>(pObject))
	{
		pMonster->OnHit();
	}
}

void CHitScanSkill::OnCollision(TCollisionCtx Ctx)
{
}

void CHitScanSkill::OnCollisionEnd(TCollisionCtx Ctx)
{
}
