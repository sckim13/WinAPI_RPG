#include "pch.h"
#include "CPlayer.h"
#include "CKeyManager.h"
#include "CMainGame.h"
#include "CTimeManager.h"
#include "CTexture.h"
#include "CPathManager.h"
#include "CResourceManager.h"
#include "CCollider.h"
#include "CTransform.h"
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

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{	
	__super::Initialize();

	m_eObjectType = EObjectType::PLAYER;
	wstring wstrName = L"Player_" + to_wstring(GetID());
	SetName(wstrName);

	CItemManager::GetInstance()->SetPlayer(this);


	m_pTexture = CResourceManager::GetInstance()->LoadTexture(L"Player", L"Texture\\Player.bmp");
	m_pTexture->SetOwner(this);
	m_pCollider = new CCollider;
	m_pCollider->Initialize();
	m_pCollider->SetOwner(this);

	/* later refactoring skill management */
	CSkill* pSkill = new CHitScanSkill;
	pSkill->Initialize();
	m_vecSkills.push_back(pSkill);

	m_pCollider->m_hOnCollisionBegin->AddBinding(this, [this](TCollisionCtx Ctx) { OnCollisionBegin(Ctx); });
	m_pCollider->m_hOnCollisionEnd->AddBinding(this, [this](TCollisionCtx Ctx) { OnCollisionEnd(Ctx); });

	m_pInventory = new CInventory;
	m_pInventory->Initialize();
	m_pEquipment = new CEquipment;
	m_pEquipment->Initialize();
}

void CPlayer::PostInitialize()
{
}

void CPlayer::Update()
{
	SortCollisionList();

	float fDT = CTimeManager::GetInstance()->GetDeltaTime();

	if (CKeyManager::GetInstance()->GetKeyState(EKey::LEFT) == EKeyState::HOLD
		&& CKeyManager::GetInstance()->GetKeyState(EKey::RIGHT) == EKeyState::HOLD)
	{
	}
	else if (CKeyManager::GetInstance()->GetKeyState(EKey::LEFT) == EKeyState::HOLD)
	{
		m_ePoseDir = EPoseDirection::LEFT;
		m_ePlayerState = EPlayerState::WALK;
		SetPosition(GetPosition() + fDT * Vec2{ -200.f, 0.f });
	}
	else if (CKeyManager::GetInstance()->GetKeyState(EKey::RIGHT) == EKeyState::HOLD)
	{
		m_ePoseDir = EPoseDirection::RIGHT;
		m_ePlayerState = EPlayerState::WALK;
		SetPosition(GetPosition() + fDT * Vec2{ 200.f, 0.f });
	}
	else if (CKeyManager::GetInstance()->GetKeyState(EKey::UP) == EKeyState::HOLD)
	{
		m_ePlayerState = EPlayerState::WALK;
		SetPosition(GetPosition() + fDT * Vec2{ 0.f, -200.f });
	}
	else if (CKeyManager::GetInstance()->GetKeyState(EKey::DOWN) == EKeyState::HOLD)
	{
		m_ePlayerState = EPlayerState::WALK;
		SetPosition(GetPosition() + fDT * Vec2{ 0.f, 200.f });
	}
	else
	{
		m_ePlayerState = EPlayerState::IDLE;
	}
}

void CPlayer::LateUpdate()
{
	GetCollider()->LateUpdate();
}

void CPlayer::Release()
{
	CItemManager::GetInstance()->SetPlayer(nullptr);
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

	GetTexture()->Render(hDC, (int)GetPosition().x, (int)GetPosition().y, m_ePoseDir);

	//TransparentBlt(
	//	hDC,
	//	(int)(vPos.x - (float)(iWidth / 2)),
	//	(int)(vPos.y - (float)(iHeight / 2)),
	//	iWidth, iHeight,
	//	GetTexture()->GetDC(),
	//	0, 0, iWidth, iHeight,
	//	RGB(255, 255, 255)
	//);

	GetCollider()->Render(hDC);
}

void CPlayer::OnCollisionBegin(TCollisionCtx Ctx)
{
	CObject* pObject = Ctx.pCounterPart->GetOwner();
	m_vecObjectsOnCollision[(int)pObject->GetObjectType()].push_back(pObject);

	if (dynamic_cast<CMonster*>(pObject))
	{
	}
}

void CPlayer::OnCollision(TCollisionCtx Ctx)
{
}

void CPlayer::OnCollisionEnd(TCollisionCtx Ctx)
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

void CPlayer::OnKeyEventTriggered(TKeyEventCtx Ctx)
{
	auto [eKeyEvent, eKeyState] = Ctx;

	if (eKeyEvent == EEventType::PICKITEM)
	{
		if (!m_vecObjectsOnCollision[(int)EObjectType::ITEM].empty())
		{
			CItem* pItem = dynamic_cast<CItem*>(m_vecObjectsOnCollision[(int)EObjectType::ITEM].front());
			pItem->SetOwner(this);
			pItem->SetPosition(GetPosition());
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
		m_vecSkills[0]->Execute();
	}
}

void CPlayer::OnHit()
{
	cout << "[Player] Hit" << endl;
}

void CPlayer::OnDead()
{
	cout << "[Player] Die" << endl;
}
