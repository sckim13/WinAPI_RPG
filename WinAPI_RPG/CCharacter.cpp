#include "pch.h"
#include "CCharacter.h"
#include "CMovementComponent.h"

CCharacter::CCharacter() : m_llHP(10000000000), m_llMaxHP(10000000000)
{
}

CCharacter::~CCharacter()
{
	Release();
}

void CCharacter::Initialize()
{
	// TODO 나중에 일반화, 지금은 플레이어에만
	//m_pMovementComponent = new CMovementComponent;
	//m_pMovementComponent->AttachTo(this);

	__super::Initialize();
}

void CCharacter::PostInitialize()
{
	__super::PostInitialize();
}

void CCharacter::Update()
{
	__super::Update();
}

void CCharacter::LateUpdate()
{
	__super::LateUpdate();
}

void CCharacter::Release()
{
}

void CCharacter::Render(HDC hDC)
{
}

void CCharacter::OnCollisionBegin(const TCollisionCtx& Ctx)
{
}

void CCharacter::OnCollision(const TCollisionCtx& Ctx)
{
}

void CCharacter::OnCollisionEnd(const TCollisionCtx& Ctx)
{
}
