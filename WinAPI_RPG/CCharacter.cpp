#include "pch.h"
#include "CCharacter.h"

CCharacter::CCharacter() : m_ePoseDir(EPoseDirection::LEFT)
{
	Initialize();
}

CCharacter::~CCharacter()
{
}

void CCharacter::Initialize()
{
	__super::Initialize();
}

void CCharacter::PostInitialize()
{
}

void CCharacter::Update()
{
}

void CCharacter::LateUpdate()
{
}

void CCharacter::Release()
{
}

void CCharacter::Render(HDC hDC)
{
}

void CCharacter::OnCollisionBegin(TCollisionCtx Ctx)
{
}

void CCharacter::OnCollision(TCollisionCtx Ctx)
{
}

void CCharacter::OnCollisionEnd(TCollisionCtx Ctx)
{
}
