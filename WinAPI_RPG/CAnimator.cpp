#include "pch.h"
#include "CAnimator.h"
#include "CTexture.h"

CAnimator::CAnimator() : m_iWidth(0), m_iHeight(0), m_bLoop(false), m_iFrameDelay{}, m_iFrameSize(0)
{
}

CAnimator::~CAnimator()
{
}

void CAnimator::Initialize()
{
}

void CAnimator::PostInitialize()
{
}

void CAnimator::Update()
{
}

void CAnimator::LateUpdate()
{
}

void CAnimator::Release()
{
}

void CAnimator::Render(HDC hDC)
{
	m_pTexture->Render(hDC);
}

void CAnimator::Play()
{

}
