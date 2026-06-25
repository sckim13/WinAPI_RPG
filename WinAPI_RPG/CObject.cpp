#include "pch.h"
#include "CObject.h"
#include "CTransform.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CKeyManager.h"

CObject::CObject() : m_pTexture(nullptr), m_pCollider(nullptr), m_wstrName{}
{
}

CObject::~CObject()
{
	Release();
}

void CObject::Initialize()
{
	CKeyManager::GetInstance()->m_hOnKeyEventTriggered->AddBinding(
		this,
		[this](TKeyEventCtx Ctx) { OnKeyEventTriggered(Ctx); }
	);
}

void CObject::PostInitialize()
{
	for (CComponent* pComponent : m_vecComponent)
	{
		pComponent->Initialize();
	}
}

void CObject::Update()
{
}

void CObject::LateUpdate()
{
	for (CComponent* pComponent : m_vecComponent)
	{
		pComponent->Update();
	}
}

void CObject::Release()
{
	for (CComponent* pComponent : m_vecComponent)
	{
		Safe_Delete<CComponent*>(pComponent);
	}
	m_vecComponent.clear();
}

void CObject::AddComponent(CComponent* pComponent)
{
	m_vecComponent.push_back(pComponent);
}

void CObject::OnKeyEventTriggered(TKeyEventCtx Ctx)
{
}
