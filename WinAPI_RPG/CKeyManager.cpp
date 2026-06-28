#include "pch.h"
#include "CKeyManager.h"
#include "CTimeManager.h"
#include "CMainGame.h"
#include "CUIManager.h"

vector<int> g_vecVK =
{
	// Alphabet Layer
	'A',
	'B',
	'C',
	'D',
	'E',
	'F',
	'G',
	'H',
	'I',
	'J',
	'K',
	'L',
	'M',
	'N',
	'O',
	'P',
	'Q',
	'R',
	'S',
	'T',
	'U',
	'V',
	'W',
	'X',
	'Y',
	'Z',
	VK_OEM_COMMA,   // ,
	VK_OEM_PERIOD,  // .
	VK_OEM_2,       // /  ?
	VK_OEM_1,       // ;  :
	VK_OEM_7,       // '  "
	VK_OEM_4,       // [  {
	VK_OEM_6,       // ]  }

	// Upper Number Layer
	VK_OEM_3,       // `  ~
	'0',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',
	VK_OEM_MINUS,   // -
	VK_OEM_PLUS,    // =  +  (Shift 안 누른 상태에서도 이 키)

	// Function Key Layer
	VK_F1,
	VK_F2,
	VK_F3,
	VK_F4,
	VK_F5,
	VK_F6,
	VK_F7,
	VK_F8,
	VK_F9,
	VK_F10,
	VK_F11,
	VK_F12,

	// Arrow Key
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,

	// Peripheral
	VK_ESCAPE,
	VK_TAB,
	VK_CAPITAL,
	VK_SHIFT,
	VK_CONTROL,
	VK_MENU,
	VK_SPACE,
	VK_RETURN,
	VK_OEM_5,       // \  |  (RSLASH)
	VK_BACK,

	// Arrow Upper Layer
	VK_SNAPSHOT,
	VK_SCROLL,
	VK_PAUSE,
	VK_INSERT,
	VK_HOME,
	VK_PRIOR,       // Page Up
	VK_DELETE,
	VK_END,
	VK_NEXT,        // Page Down

	// Mouse
	VK_LBUTTON,
	VK_RBUTTON,
	VK_MBUTTON,

	// MAX
};

map<EKey, EEventType> g_mapInputEvent =
{
	// keyboard events
	{EKey::I, EEventType::UI_INVENTORY},
	{EKey::E, EEventType::UI_EQUIPMENT},
	{EKey::Z, EEventType::PICKITEM},
	{EKey::SPACE, EEventType::NPC},
	{EKey::CTRL, EEventType::SKILL_DEFAULT},

	// mouse events
	{EKey::L_CLICK, EEventType::MOUSE_L_CLICK},
	{EKey::R_CLICK, EEventType::MOUSE_R_CLICK},
	{EKey::M_CLICK, EEventType::MOUSE_M_CLICK},
};

CKeyManager::CKeyManager()
{

}

CKeyManager::~CKeyManager()
{
	Release();
}

void CKeyManager::Initialize()
{
	m_OnKeyEventTriggered = new CEventDelegate<TKeyEventCtx>;
	m_OnMouseEventTriggered = new CEventDelegate<TMouseEventCtx>;

	for (int i = 0; i < (int)EKey::MAX; ++i)
	{
		m_vecKey.push_back(tKeyInfo{});
	}

	for (int i = 0; i < (int)EKey::MAX; ++i)
	{
		auto iter = g_mapInputEvent.find((EKey)i);
		if (iter != g_mapInputEvent.end())
		{
			m_mapInputEvent.insert(*iter);
		}
		else
		{
			m_mapInputEvent.insert({ (EKey)i, EEventType::NONE });
		}
	}
}

void CKeyManager::PostInitialize()
{
}

void CKeyManager::Update()
{
	/* Key State updating */
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
						cout << "[Key Manager] Key \"" << magic_enum::enum_name((EKey)i) << "\" Double Pressed" << endl;
						m_vecKey[i].eKeyState = EKeyState::DOUBLE_PRESSED;
					}
					else
					{
						cout << "[Key Manager] Key \"" << magic_enum::enum_name((EKey)i) << "\" Pressed" << endl;
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
					cout << "[Key Manager] Key \"" << magic_enum::enum_name((EKey)i) << "\" Released" << endl;
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

	/* Event Broadcasting */
	for (int i = 0; i < (int)EKey::MAX; ++i)
	{
		if (m_vecKey[i].eKeyState == EKeyState::NONE || m_mapInputEvent[(EKey)i] == EEventType::NONE)
		{
			continue;
		}
		else if (m_mapInputEvent[(EKey)i] > EEventType::MOUSE_NONE && m_mapInputEvent[(EKey)i] < EEventType::MOUSE_MAX)
		{
			/* UI Mouse Event Handling */
			// cout << "[Key Manager] Event " << magic_enum::enum_name(m_mapInputEvent[(EKey)i]) << ", " << magic_enum::enum_name(m_vecKey[i].eKeyState) << " is triggered" << endl;
			m_OnMouseEventTriggered->Broadcast(TMouseEventCtx{ (EKey)i, m_vecKey[i].eKeyState, Vec2{0.f, 0.f} });
		}
		else
		{
			/* Key Event Handling */
			// cout << "[Key Manager] Event " << magic_enum::enum_name(m_mapInputEvent[(EKey)i]) << " is triggered" << endl;
			m_OnKeyEventTriggered->Broadcast(TKeyEventCtx{ m_mapInputEvent[(EKey)i], m_vecKey[i].eKeyState });
		}
	}

}

void CKeyManager::LateUpdate()
{
}

void CKeyManager::Release()
{
	Safe_Delete<CEventDelegate<TKeyEventCtx>*>(m_OnKeyEventTriggered);
	Safe_Delete<CEventDelegate<TMouseEventCtx>*>(m_OnMouseEventTriggered);
}

void CKeyManager::Render(HDC hDC)
{
}
