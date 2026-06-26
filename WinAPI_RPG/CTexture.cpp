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

void CTexture::PostInitialize()
{
}

void CTexture::Update()
{
}

void CTexture::LateUpdate()
{
}

void CTexture::Release()
{
}

void CTexture::Render(HDC hDC)
{
}

void CTexture::Render(HDC hDC, int iX, int iY, bool bFlipped)
{
	StretchBlt(
		hDC,
		iX, iY,
		(!bFlipped ? 1 : -1) * GetWidth(), GetHeight(),
		m_hDC,
		0, 0,
		GetWidth(), GetHeight(),
		SRCCOPY);
}

void CTexture::Render(HDC hDC, int iDstX, int iDstY, int iSrcX, int iSrcY, int iCX, int iCY, bool bFlipped)
{
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(hDC,
		iDstX, iDstY,
		iCX, iCY,
		m_hDC, 
		iSrcX, iSrcY,
		iCX, iCY,
		bf
	);
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
