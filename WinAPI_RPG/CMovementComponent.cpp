#include "pch.h"
#include "CMovementComponent.h"
#include "CKeyManager.h"
#include "CTimeManager.h"
#include "CPlayer.h"

CMovementComponent::CMovementComponent()
{
}

CMovementComponent::~CMovementComponent()
{
}

void CMovementComponent::Initialize()
{
}

void CMovementComponent::PostInitialize()
{
}

void CMovementComponent::Update()
{
	float fDT = CTimeManager::GetInstance()->GetDeltaTime();

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetOwner());

	if (CKeyManager::GetInstance()->GetKeyState(EKey::LEFT) == EKeyState::HOLD
		&& CKeyManager::GetInstance()->GetKeyState(EKey::RIGHT) == EKeyState::HOLD)
	{
	}
	else if (CKeyManager::GetInstance()->GetKeyState(EKey::LEFT) == EKeyState::HOLD)
	{
		pPlayer->Flip(false);
		pPlayer->SetAnimState(EPlayerAnimState::WALK);
		pPlayer->SetPosition(pPlayer->GetPosition() + fDT * Vec2{ -200.f, 0.f });
	}
	else if (CKeyManager::GetInstance()->GetKeyState(EKey::RIGHT) == EKeyState::HOLD)
	{
		pPlayer->Flip(true);
		pPlayer->SetAnimState(EPlayerAnimState::WALK);
		pPlayer->SetPosition(pPlayer->GetPosition() + fDT * Vec2{ 200.f, 0.f });
	}
	else if (CKeyManager::GetInstance()->GetKeyState(EKey::UP) == EKeyState::HOLD)
	{
		pPlayer->Flip(false);
		pPlayer->SetAnimState(EPlayerAnimState::WALK);
		pPlayer->SetPosition(pPlayer->GetPosition() + fDT * Vec2{ 0.f, -200.f });
	}
	else if (CKeyManager::GetInstance()->GetKeyState(EKey::DOWN) == EKeyState::HOLD)
	{
		pPlayer->Flip(false);
		pPlayer->SetAnimState(EPlayerAnimState::WALK);
		pPlayer->SetPosition(pPlayer->GetPosition() + fDT * Vec2{ 0.f, 200.f });
	}
	else
	{
		pPlayer->SetAnimState(EPlayerAnimState::STAND);
	}
}

void CMovementComponent::LateUpdate()
{
}

void CMovementComponent::Release()
{
}

void CMovementComponent::Render(HDC hDC)
{
}
