#pragma once

#include "CResource.h"

class CTexture : public CResource
{
public:
	CTexture();
	virtual ~CTexture();

	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	// for single image
	virtual void Render(HDC hDC, int iX, int iY);
	// for animation sprite
	virtual void Render(HDC hDC, int iDstX, int iDstY, int iSrcX, int iSrcY, int iCX, int iCY);

	void LoadBMP(const wstring& strPath);
	void LoadPNG(const wstring& strPath);

	inline UINT GetWidth() { return m_bitInfo.bmWidth; }
	inline UINT GetHeight() { return m_bitInfo.bmHeight; }
	inline IPoint GetSize() { return IPoint{ m_bitInfo.bmWidth , m_bitInfo.bmHeight }; }

	inline HDC GetDC() { return m_hDC; }

	inline void SetType(ETextureType eType) { m_eTextureType = eType; }

private:
	ETextureType m_eTextureType;

	HDC m_hDC;
	HBITMAP m_hBit;

	// BMP
	BITMAP m_bitInfo;
};

