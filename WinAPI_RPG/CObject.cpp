#include "pch.h"
#include "CObject.h"
#include "CTransform.h"
#include "CTexture.h"
#include "CCollider.h"

CObject::CObject() : m_pTransform(nullptr), m_pTexture(nullptr), m_pCollider(nullptr)
{
}

CObject::~CObject()
{
	Release();
}

void CObject::Initialize()
{
}

void CObject::PostInitialize()
{
}

void CObject::Update()
{
}

void CObject::LateUpdate()
{
}

void CObject::Release()
{
	Safe_Delete<CTransform*>(m_pTransform);
	Safe_Delete<CTexture*>(m_pTexture);
	Safe_Delete<CCollider*>(m_pCollider);
}

void CObject::Render(HDC hDC)
{
}
