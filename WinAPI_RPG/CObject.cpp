#include "pch.h"
#include "CObject.h"
#include "CTransform.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CKeyManager.h"

CObject::CObject() : m_pTextureComponent(nullptr), m_pCollider(nullptr), m_wstrName{}, m_bFlipped(false)
{
}

CObject::~CObject()
{
	Release();
}

void CObject::Initialize()
{
	CKeyManager::GetInstance()->m_OnKeyEventTriggered->AddBinding(
		GetID(),
		[this](const TKeyEventCtx& Ctx) { OnKeyEventTriggered(Ctx); }
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

void CObject::OnKeyEventTriggered(const TKeyEventCtx& Ctx)
{
}
