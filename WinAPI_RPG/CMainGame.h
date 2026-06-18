#pragma once
#include "CManager.h"

class CMainGame : public CManager
{
	SINGLETON(CMainGame);

public:
	virtual void Initialize() override;
	HRESULT Initialize(HWND hWnd, POINT WndResolution);
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;
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

