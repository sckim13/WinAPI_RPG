#include "pch.h"
#include "CKeyManager.h"
#include "CTimeManager.h"
#include "CMainGame.h"

vector<int> g_vecVK =
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,

	VK_ESCAPE,

	// MAX
};

CKeyManager::CKeyManager()
{
}

CKeyManager::~CKeyManager()
{
}

void CKeyManager::Initialize()
{
	for (int i = 0; i < (int)EKey::MAX; ++i)
	{
		m_vecKey.push_back(tKeyInfo{});
	}
}

void CKeyManager::Update()
{	
	HWND hWnd = GetFocus();

	if (hWnd)
	{
		for (int i = 0; i < (int)EKey::MAX; ++i)
		{
			if (GetAsyncKeyState(g_vecVK[i]) & 0x8000)
			{
				if (m_vecKey[i].bPressedOnLastUpdate)
				{
					m_vecKey[i].eKeyState = EKeyState::HOLD;
				}
				else
				{
					float fPressedInterval = CTimeManager::GetInstance()->GetTime() - m_vecKey[i].fLastPressedTime;
					if (fPressedInterval < fDoubleClickThreshold)
					{
						cout << "Double Pressed!" << endl;
						m_vecKey[i].eKeyState = EKeyState::DOUBLE_PRESSED;
					}
					else
					{
						m_vecKey[i].eKeyState = EKeyState::PRESSED;
					}
				}

				m_vecKey[i].bPressedOnLastUpdate = true;
				m_vecKey[i].fLastPressedTime = CTimeManager::GetInstance()->GetTime();
			}
			else
			{
				if (m_vecKey[i].bPressedOnLastUpdate)
				{
					m_vecKey[i].eKeyState = EKeyState::RELEASED;
				}
				else
				{
					m_vecKey[i].eKeyState = EKeyState::NONE;
				}

				m_vecKey[i].bPressedOnLastUpdate = false;
			}
		}
	}
	else
	{
		for (int i = 0; i < (int)EKey::MAX; ++i)
		{
			if (m_vecKey[i].eKeyState == EKeyState::PRESSED
				|| m_vecKey[i].eKeyState == EKeyState::DOUBLE_PRESSED
				|| m_vecKey[i].eKeyState == EKeyState::HOLD)
			{
				m_vecKey[i].eKeyState = EKeyState::RELEASED;
			}
			else
			{
				m_vecKey[i].eKeyState = EKeyState::NONE;
			}
		}
	}
}

void CKeyManager::Release()
{
}
