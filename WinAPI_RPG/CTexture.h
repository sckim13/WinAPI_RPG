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

	virtual void Render(HDC hDC, int iX, int iY, EPoseDirection bDir = EPoseDirection::LEFT);

	void Load(const wstring& strPath);

	inline UINT GetWidth() { return m_bitInfo.bmWidth; }
	inline UINT GetHeight() { return m_bitInfo.bmHeight; }
	inline Vec2 GetSize() { return Vec2{ m_bitInfo.bmWidth , m_bitInfo.bmHeight }; }

	inline HDC GetDC() { return m_hDC; }

private:

	HDC m_hDC;
	HBITMAP m_hBit;

	BITMAP m_bitInfo;

};

