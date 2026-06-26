#include "pch.h"
#include "CCharacter.h"

CCharacter::CCharacter()
{
}

CCharacter::~CCharacter()
{
	Release();
}

void CCharacter::Initialize()
{
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
