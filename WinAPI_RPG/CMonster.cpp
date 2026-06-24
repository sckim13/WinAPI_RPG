#include "pch.h"
#include "CMonster.h"
#include "CTransform.h"
#include "CCollider.h"
#include "CResourceManager.h"
#include "CTexture.h"
#include "CPlayer.h"
#include "EventContext.h"
#include "CTimeManager.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
}

void CMonster::Initialize()
{
	__super::Initialize();

	m_eObjectType = EObjectType::MONSTER;
	wstring wstrName = L"Monster_" + to_wstring(GetID());
	SetName(wstrName);

	m_pTexture = CResourceManager::GetInstance()->LoadTexture(L"Monster", L"Texture\\Monster.bmp");
	m_pTexture->SetOwner(this);
	m_pCollider = new CCollider;
	m_pCollider->Initialize();
	m_pCollider->SetOwner(this);

	/* bind event to collider */
	GetCollider()->m_hOnCollisionBegin->AddBinding(this, [this](TCollisionCtx Ctx) { OnCollisionBegin(Ctx); });
}

void CMonster::PostInitialize()
{
}

void CMonster::Update()
{
	Vec2 vPos = GetPosition();
	float fDT = CTimeManager::GetInstance()->GetDeltaTime();

	SetPosition(Vec2{ vPos.x, vPos.y });
}

void CMonster::LateUpdate()
{
	GetCollider()->LateUpdate();
}

void CMonster::Release()
{
	GetCollider()->m_hOnCollisionBegin->DeleteBinding(this);
}

void CMonster::Render(HDC hDC)
{
	GetTexture()->Render(hDC, (int)GetPosition().x, (int)GetPosition().y);

	GetCollider()->Render(hDC);
}

void CMonster::OnCollisionBegin(TCollisionCtx Ctx)
{
	CObject* pObject = Ctx.pCounterPart->GetOwner();

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObject);
	if (pPlayer)
	{
		pPlayer->OnHit();
	}
}

void CMonster::OnCollision(TCollisionCtx Ctx)
{
}

void CMonster::OnCollisionEnd(TCollisionCtx Ctx)
{
}

void CMonster::OnHit()
{
	cout << "[Monster] Hit by Player" << endl;
}

void CMonster::OnDead()
{
	cout << "[Monster] Dead" << endl;
}

