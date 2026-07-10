#include "pch.h"
#include "CPlayer.h"
#include "CKeyManager.h"
#include "CMainGame.h"
#include "CTimeManager.h"
#include "CTextureComponent.h"
#include "CPathManager.h"
#include "CResourceManager.h"
#include "CCollider.h"
#include "CSkill.h"
#include "CInventory.h"
#include "CEquipment.h"
#include "CItem.h"
#include "CUIManager.h"
#include "CInventoryUI.h"
#include "MathUtil.h"
#include "CItemManager.h"
#include "CMonster.h"
#include "CHitScanSkill.h"
#include "CSkillComponent.h"
#include "CActiveSkill.h"
#include "CSceneManager.h"
#include "CTimerManager.h"
#include "CMovementComponent.h"
#include "CCameraManager.h"

CPlayer::CPlayer() : m_bOnKeyEventCoolDown(false)
{
	m_eObjectType = EObjectType::PLAYER;
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{	
	wstring wstrName = L"Player_" + to_wstring(GetID());
	SetName(wstrName);

	m_pTextureComponent = new CTextureComponent;
	m_pTextureComponent->SetOwner(this);
	m_pTextureComponent->BindTexture(L"Player");

	m_pCollider = new CCollider;
	m_pCollider->AttachTo(this);

	m_pSkillComponent = new CSkillComponent;
	m_pSkillComponent->AttachTo(this);

	m_pInventory = new CInventory;
	m_pInventory->AttachTo(this);
	
	m_pEquipment = new CEquipment;
	m_pEquipment->AttachTo(this);

	m_pMovementComponent = new CMovementComponent;
	m_pMovementComponent->AttachTo(this);

	__super::Initialize();
}

void CPlayer::PostInitialize()
{
	m_pCollider->m_OnCollisionBegin->AddBinding(GetID(), [this](const TCollisionCtx& Ctx) { OnCollisionBegin(Ctx); });
	m_pCollider->m_OnCollisionEnd->AddBinding(GetID(), [this](const TCollisionCtx& Ctx) { OnCollisionEnd(Ctx); });

	// TODO Temp Cooldown 1sec
	CTimerManager::GetInstance()->SetTimer(
		m_KeyEventCoolDownHandle,
		[this]() { SetKeyEventEnabled(); },
		1.f, true
	);

	__super::PostInitialize();
}

void CPlayer::Update()
{
	__super::Update();

	SortCollisionList();

	UpdateScroll();
}

void CPlayer::LateUpdate()
{
	__super::LateUpdate();
}

void CPlayer::Release()
{
	m_pCollider->m_OnCollisionBegin->DeleteBinding(GetID());
	m_pCollider->m_OnCollisionEnd->DeleteBinding(GetID());
}

void CPlayer::Render(HDC hDC)
{
	/*
	Rectangle(
		hDC,
		(int)GetPosition().x - (int)(GetScale().x / 2),
		(int)GetPosition().y - (int)(GetScale().y / 2),
		(int)GetPosition().x + (int)(GetScale().x / 2),
		(int)GetPosition().y + (int)(GetScale().y / 2)
	);
	BitBlt(
		CMainGame::GetInstance()->GetMemDC(),
		(int)(vPos.x - (float)(iWidth / 2)),
		(int)(vPos.y - (float)(iHeight / 2)),
		iWidth, iHeight,
		m_pTexture->GetDC(),
		0, 0, SRCCOPY
	);
	*/

	GetTextureComponent()->Render(hDC);

	//TransparentBlt(
	//	hDC,
	//	(int)(vPos.x - (float)(iWidth / 2)),
	//	(int)(vPos.y - (float)(iHeight / 2)),
	//	iWidth, iHeight,
	//	GetTextureComponent()->GetDC(),
	//	0, 0, iWidth, iHeight,
	//	RGB(255, 255, 255)
	//);

	GetCollider()->Render(hDC);
}

void CPlayer::OnCollisionBegin(const TCollisionCtx& Ctx)
{
	CObject* pObject = Ctx.pCounterPart->GetOwner();
	m_vecObjectsOnCollision[(int)pObject->GetObjectType()].push_back(pObject);

	if (dynamic_cast<CMonster*>(pObject))
	{
		wcout << "[Player] " << GetName() << " hit by " << pObject->GetName() << endl;
	}
}

void CPlayer::OnCollision(const TCollisionCtx& Ctx)
{
}

void CPlayer::OnCollisionEnd(const TCollisionCtx& Ctx)
{
	CObject* pObject = Ctx.pCounterPart->GetOwner();
	auto iter = find(m_vecObjectsOnCollision[(int)pObject->GetObjectType()].begin(),
		m_vecObjectsOnCollision[(int)pObject->GetObjectType()].end(), pObject);
	assert(iter != m_vecObjectsOnCollision[(int)pObject->GetObjectType()].end());

	m_vecObjectsOnCollision[(int)pObject->GetObjectType()].erase(iter);
}

void CPlayer::SortCollisionList()
{
	auto F = [this](CObject* lhs, CObject* rhs)
		{
			float fDistL = MathUtil::Distance(this, lhs);
			float fDistR = MathUtil::Distance(this, rhs);
			return fDistL < fDistR;
		};
	for (int i = 0; i < (int)EObjectType::MAX; ++i)
	{
		sort(m_vecObjectsOnCollision[i].begin(), m_vecObjectsOnCollision[i].end(), F);
	}
}

void CPlayer::UpdateScroll()
{
	CCameraManager::GetInstance()->UpdateScroll(GetPosition());
}

void CPlayer::OnKeyEventTriggered(const TKeyEventCtx& Ctx)
{
	if (IsKeyEventCoolDown()) return;

	auto [eKeyEvent, eKeyState] = Ctx;

	m_bOnKeyEventCoolDown = true;
	CTimerManager::GetInstance()->RestartTimer(m_KeyEventCoolDownHandle);

	if (eKeyEvent == EEventType::PICKITEM)
	{
		if (!m_vecObjectsOnCollision[(int)EObjectType::ITEM].empty())
		{
			CItem* pItem = dynamic_cast<CItem*>(m_vecObjectsOnCollision[(int)EObjectType::ITEM].front());
			pItem->SetOwner(this);
			pItem->SetPosition(Vec2{0.f, 0.f});
			pItem->GetCollider()->SetEnabled(false);
			m_pInventory->PushItem(pItem);
			wcout << "[Player] Grab item : " << pItem->GetName() << endl;
		}
		else
		{
			wcout << "[Player] No item to pick" << endl;
		}
	}
	
	if (eKeyEvent == EEventType::SKILL_DEFAULT)
	{
		cout << "[Player] Basic Attack" << endl;
		CActiveSkill* pSkill = m_pSkillComponent->CreateSkill(L"ActiveSkill");
	}
}

void CPlayer::OnHit(long long llDamage)
{
	m_llHP -= llDamage;
	cout << "[Player] Hit" << endl;
}

void CPlayer::OnDead()
{
	cout << "[Player] Die" << endl;
}
