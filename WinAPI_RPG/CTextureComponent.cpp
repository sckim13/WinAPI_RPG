#include "pch.h"
#include "CTextureComponent.h"
#include "CResourceManager.h"
#include "CTexture.h"
#include "CObject.h"
#include "CCameraManager.h"

CTextureComponent::CTextureComponent() : m_pTexture(nullptr), m_bScrollEnabled(true)
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
	IPoint ptScroll = CCameraManager::GetInstance()->GetScroll();

	if (m_pTexture)
	{
		if (GetOwner())
		{
			if (m_bScrollEnabled)
			{
				// For normal object case
				m_pTexture->Render(hDC, (int)(GetOwner()->GetPosition().x) + ptScroll.x, (int)(GetOwner()->GetPosition().y) + ptScroll.y);
			}
			else
			{
				// UI case
				m_pTexture->Render(hDC, (int)(GetOwner()->GetPosition().x), (int)(GetOwner()->GetPosition().y));
			}
		}
		else
		{
			// For map case
			m_pTexture->Render(hDC, ptScroll.x, ptScroll.y);
		}
	}
}

void CTextureComponent::Render(HDC hDC, int iOffsetX, int iOffsetY)
{
	IPoint ptScroll = CCameraManager::GetInstance()->GetScroll();

	if (m_pTexture)
	{
		if (GetOwner())
		{
			if (m_bScrollEnabled)
			{
				// For normal object case
				m_pTexture->Render(hDC, (int)(GetOwner()->GetPosition().x) + ptScroll.x + iOffsetX, (int)(GetOwner()->GetPosition().y) + ptScroll.y + iOffsetY);
			}
			else
			{
				// UI case
				m_pTexture->Render(hDC, (int)(GetOwner()->GetPosition().x), (int)(GetOwner()->GetPosition().y));
			}
		}
		
	}
}

void CTextureComponent::BindTexture(const wstring& wstrName)
{
	m_pTexture = CResourceManager::GetInstance()->LoadTexture(wstrName);
}

IPoint CTextureComponent::GetTextureSize()
{
	if (m_pTexture)
	{
		return m_pTexture->GetSize();
	}
	return IPoint{0.f, 0.f};
}
