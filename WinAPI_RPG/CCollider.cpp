#include "pch.h"
#include "CCollider.h"
#include "CObjectBase.h"
#include "CMainGame.h"

CCollider::CCollider()
{
}

CCollider::~CCollider()
{
}

void CCollider::Initialize()
{
}

void CCollider::Update()
{
	// SetPosition(m_pOwner->GetPosition());
}

void CCollider::Release()
{
}

void CCollider::Render(HDC hDC)
{
	Rectangle(hDC, 50, 50, 100, 100);
}
