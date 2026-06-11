#pragma once

class CCore
{
	SINGLETON(CCore);

public:
	HRESULT Initialize(HWND hWnd, POINT WndResolution);
	void Update();
	void Render();

	inline HWND GetHWnd() { return m_hWnd; }

private:
	HWND m_hWnd;
	POINT m_WndResolution;
	HDC m_hDC;

	HBITMAP m_hBitmap;
	HDC m_hDCMem;

};

