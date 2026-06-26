#include "pch.h"
#include "CTextureComponent.h"
#include "CResourceManager.h"
#include "CTexture.h"
#include "CObject.h"

CTextureComponent::CTextureComponent() : m_pTexture(nullptr)
{
}

CTextureComponent::~CTextureComponent()
{
	Release();
}

void CTextureComponent::Initialize()
{
}

void CTextureComponent::PostInitialize()
{
}

void CTextureComponent::Update()
{
}

void CTextureComponent::LateUpdate()
{
}

void CTextureComponent::Release()
{
	/* Do not delete texture pointer. ResourceManager controls all resource base pointer life cycle */
	m_pTexture = nullptr;
}

void CTextureComponent::Render(HDC hDC)
{
	if (m_pTexture)
	{
		m_pTexture->Render(hDC, (int)GetOwner()->GetPosition().x, (int)GetOwner()->GetPosition().y, GetOwner()->IsFlipped());
	}
}

void CTextureComponent::Render(HDC hDC, int iOffsetX, int iOffsetY)
{
	if (m_pTexture)
	{
		m_pTexture->Render(hDC, (int)GetOwner()->GetPosition().x + iOffsetX, (int)GetOwner()->GetPosition().y + iOffsetY, GetOwner()->IsFlipped());
	}
}

void CTextureComponent::BindTexture(const wstring& wstrName)
{
	m_pTexture = CResourceManager::GetInstance()->LoadTexture(wstrName);
}

Vec2 CTextureComponent::GetTextureSize()
{
	if (m_pTexture)
	{
		return m_pTexture->GetSize();
	}
	return Vec2{0.f, 0.f};
}
