#include "pch.h"
#include "CMonster.h"
#include "CTransform.h"
#include "CCollider.h"
#include "CResourceManager.h"
#include "CTextureComponent.h"
#include "CPlayer.h"
#include "EventContext.h"
#include "CTimeManager.h"
#include "CCombatManager.h"

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

	m_pTextureComponent = new CTextureComponent;
	m_pTextureComponent->SetOwner(this);
	m_pTextureComponent->BindTexture(L"Monster");

	m_pCollider = new CCollider;
	m_pCollider->AttachTo(this);
}

void CMonster::PostInitialize()
{
	__super::PostInitialize();

	GetCollider()->m_OnCollisionBegin->AddBinding(GetID(), [this](const TCollisionCtx& Ctx) { OnCollisionBegin(Ctx); });
}

void CMonster::Update()
{
	__super::Update();

	Vec2 vPos = GetPosition();
	float fDT = CTimeManager::GetInstance()->GetDeltaTime();

	SetPosition(Vec2{ vPos.x, vPos.y });
}

void CMonster::LateUpdate()
{
	__super::LateUpdate();
}

void CMonster::Release()
{
	GetCollider()->m_OnCollisionBegin->DeleteBinding(GetID());
}

void CMonster::Render(HDC hDC)
{
	GetTextureComponent()->Render(hDC);

	GetCollider()->Render(hDC);
}

void CMonster::OnCollisionBegin(const TCollisionCtx& Ctx)
{
	CObject* pObject = Ctx.pCounterPart->GetOwner();

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObject);
	if (pPlayer)
	{
		CCombatManager::GetInstance()->RequestDamage(pPlayer, vector<long long>{10});
	}
}

void CMonster::OnCollision(const TCollisionCtx& Ctx)
{
}

void CMonster::OnCollisionEnd(const TCollisionCtx& Ctx)
{
}

void CMonster::OnHit(long long llDamage)
{
	cout << "[Monster] Hit by Player" << endl;
	m_llHP = max(m_llHP - llDamage, 0);
	if (m_llHP == 0)
	{
		SetDead();
	}
}

void CMonster::OnDead()
{
	cout << "[Monster] Dead" << endl;
	SetDead();
}

