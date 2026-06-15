#include "pch.h"
#include "CObject.h"
#include "CCollider.h"
#include "CTransform.h"

CObject::CObject()
	: m_vPosition{}, m_fRotation(0.f), m_vScale{}, m_pOwner(nullptr), m_pTexture(nullptr), m_pTransform(nullptr), m_pCollider(nullptr)
{
}

CObject::~CObject()
{
	Safe_Delete<CObject*>(m_pOwner);
	Safe_Delete<CCollider*>(m_pCollider);
	Safe_Delete<CTransform*>(m_pTransform);
	Safe_Delete<CCollider*>(m_pCollider);
}
