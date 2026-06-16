#pragma once

#include "CResourceBase.h"

class CTexture : public CResourceBase
{
public:
	CTexture();
	virtual ~CTexture();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	virtual void Render(HDC hDC) override;

	void Load(const wstring& strPath);

	inline UINT GetWidth() { return m_bitInfo.bmWidth; }
	inline UINT GetHeight() { return m_bitInfo.bmHeight; }

	inline HDC GetDC() { return m_hDC; }

private:

	HDC m_hDC;
	HBITMAP m_hBit;

	BITMAP m_bitInfo;

};

