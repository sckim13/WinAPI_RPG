#pragma once
#include "CManagerBase.h"

class CMainGame : public CManagerBase
{
	SINGLETON(CMainGame);

public:
	HRESULT Initialize(HWND hWnd, POINT WndResolution);
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	void Render();

	inline HWND GetHWnd() { return m_hWnd; }
	inline HDC GetMemDC() { return m_hDCMem; }

private:
	HWND m_hWnd;
	POINT m_WndResolution;
	HDC m_hDC;

	HBITMAP m_hBitmap;
	HDC m_hDCMem;
};

