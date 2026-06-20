#include "pch.h"
#include "CObject.h"
#include "CTransform.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CKeyManager.h"

int CObject::g_ObjectID = 0;

CObject::CObject() : m_pTexture(nullptr), m_pCollider(nullptr), m_wstrName{}
{
}

CObject::~CObject()
{
	Release();
}

void CObject::Initialize()
{
	++g_ObjectID;

	CKeyManager::GetInstance()->m_hOnKeyEventTriggered->AddBinding(
		this,
		[this](TKeyEventCtx Ctx) { OnKeyEventTriggered(Ctx); });
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
	Safe_Delete<CTexture*>(m_pTexture);
	Safe_Delete<CCollider*>(m_pCollider);
}

void CObject::Render(HDC hDC)
{
}

void CObject::OnKeyEventTriggered(TKeyEventCtx Ctx)
{
}
