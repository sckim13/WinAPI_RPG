#include "pch.h"
#include "CCollider.h"
#include "CObject.h"

void CCollider::Initialize()
{
}

void CCollider::Update()
{
	SetPosition(m_pOwner->GetPosition());
}

void CCollider::Release()
{
}

void CCollider::Render()
{
	Rectangle(
	);
}
