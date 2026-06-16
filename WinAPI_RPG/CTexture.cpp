#include "pch.h"
#include "CTexture.h"
#include "CMainGame.h"

CTexture::CTexture() : m_hDC(nullptr), m_hBit(nullptr)
{
}

CTexture::~CTexture()
{
}

void CTexture::Initialize()
{
}

void CTexture::Update()
{
}

void CTexture::Release()
{
}

void CTexture::Render(HDC hDC)
{
}

void CTexture::Load(const wstring& strPath)
{
	m_hBit = (HBITMAP)LoadImage(nullptr, strPath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBit);

	m_hDC = CreateCompatibleDC(CMainGame::GetInstance()->GetMemDC());

	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBit);
	DeleteObject(hPrevBit);

	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}
