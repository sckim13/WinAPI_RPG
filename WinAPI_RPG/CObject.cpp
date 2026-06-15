#include "pch.h"
#include "CObject.h"
#include "CCollider.h"

CObject::CObject()
	: m_vPosition{}, m_vScale{}
{
}

CObject::~CObject()
{
	if (m_pCollider)
	{
		Safe_Delete(m_pCollider);
	}
}

void CObject::Initialize()
{
}

void CObject::Update()
{
}

void CObject::Release()
{
}

void CObject::Render()
{
}

void CObject::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->SetOwner(this);
}
