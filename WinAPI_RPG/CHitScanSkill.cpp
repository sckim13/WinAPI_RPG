#include "pch.h"
#include "CHitScanSkill.h"
#include "CMonster.h"
#include "CCollider.h"

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
}

void CHitScanSkill::PostInitialize()
{
}

void CHitScanSkill::Update()
{
}

void CHitScanSkill::LateUpdate()
{
}

void CHitScanSkill::Release()
{
}

void CHitScanSkill::Render(HDC hDC)
{
}

void CHitScanSkill::Execute()
{
	cout << "[HitScanSkill] Execute" << endl;

	/* animator play animation */
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
