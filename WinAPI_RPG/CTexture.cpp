#include "pch.h"
#include "CTexture.h"
#include "CMainGame.h"

CTexture::CTexture() : m_hDC(nullptr), m_hBit(nullptr), m_eTextureType(ETextureType::NONE)
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

void CTexture::Render(HDC hDC, int iX, int iY)
{
	switch (m_eTextureType)
	{
	case ETextureType::BMP:
	{
		TransparentBlt(
			hDC,
			iX, iY,
			GetWidth(), GetHeight(),
			m_hDC,
			0, 0,
			GetWidth(), GetHeight(),
			RGB(255, 255, 255));
		
		break;
	}
	case ETextureType::PNG:
	{
		BYTE byAlpha = 255;

		BLENDFUNCTION bf = {};
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = byAlpha;
		bf.AlphaFormat = AC_SRC_ALPHA;

		AlphaBlend(
			hDC,
			iX, iY, GetWidth(), GetHeight(),
			m_hDC,
			0, 0, GetWidth(), GetHeight(),
			bf);
		
		break;
	}
	default:
		assert(0);
		break;
	}
}

void CTexture::Render(HDC hDC, int iDstX, int iDstY, int iSrcX, int iSrcY, int iCX, int iCY)
{
	switch (m_eTextureType)
	{
	case ETextureType::BMP:
	{
		TransparentBlt(
			hDC,
			iDstX, iDstY,
			iCX, iCY,
			m_hDC,
			iSrcX, iSrcY,
			iCX, iCY,
			RGB(255, 255, 255));
		
		break;
	}
	case ETextureType::PNG:
	{
		// TODO 필요시 전역 알파 처리 코드 처리하기
		BYTE byAlpha = 255;

		BLENDFUNCTION bf = {};
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = byAlpha;
		bf.AlphaFormat = AC_SRC_ALPHA;

		AlphaBlend(
			hDC,
			iDstX, iDstY, iCX, iCY,
			m_hDC,
			iSrcX, iSrcY, iCX, iCY,
			bf);
		
		break;
	}
	default:
		assert(0);
		break;
	}
}

void CTexture::LoadBMP(const wstring& strPath)
{
	m_hBit = (HBITMAP)LoadImage(nullptr, strPath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBit);

	m_hDC = CreateCompatibleDC(CMainGame::GetInstance()->GetMemDC());

	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBit);
	DeleteObject(hPrevBit);

	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}


void CTexture::LoadPNG(const wstring& strPath)
{
	Gdiplus::Bitmap bitmap(strPath.c_str());
	if (bitmap.GetLastStatus() != Gdiplus::Ok) assert(0);

	int iWidth = bitmap.GetWidth();
	int iHeight = bitmap.GetHeight();

	// 32bit DIB Section 직접 생성
	BITMAPINFO bmi = {};
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = iWidth;
	bmi.bmiHeader.biHeight = -iHeight; // top-down
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	void* pBits = nullptr;
	m_hBit = CreateDIBSection(nullptr, &bmi, DIB_RGB_COLORS, &pBits, nullptr, 0);
	assert(m_hBit);

	// GDI+ 비트맵에서 픽셀 읽어서 premultiply 하며 복사
	Gdiplus::BitmapData bmpData;
	Gdiplus::Rect rect(0, 0, iWidth, iHeight);
	bitmap.LockBits(&rect, Gdiplus::ImageLockModeRead,
		PixelFormat32bppARGB, &bmpData);

	BYTE* pSrc = (BYTE*)bmpData.Scan0;
	BYTE* pDst = (BYTE*)pBits;

	for (int y = 0; y < iHeight; ++y)
	{
		BYTE* pSrcRow = pSrc + y * bmpData.Stride;
		BYTE* pDstRow = pDst + y * iWidth * 4;

		for (int x = 0; x < iWidth; ++x)
		{
			BYTE B = pSrcRow[x * 4 + 0];
			BYTE G = pSrcRow[x * 4 + 1];
			BYTE R = pSrcRow[x * 4 + 2];
			BYTE A = pSrcRow[x * 4 + 3];

			// premultiply
			pDstRow[x * 4 + 0] = (BYTE)(B * A / 255);
			pDstRow[x * 4 + 1] = (BYTE)(G * A / 255);
			pDstRow[x * 4 + 2] = (BYTE)(R * A / 255);
			pDstRow[x * 4 + 3] = A;
		}
	}

	bitmap.UnlockBits(&bmpData);

	m_hDC = CreateCompatibleDC(nullptr);
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBit);
	DeleteObject(hPrevBit);
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}