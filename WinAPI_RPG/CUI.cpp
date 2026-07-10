#include "pch.h"
#include "CUI.h"
#include "CKeyManager.h"
#include "CUIManager.h"
#include "MathUtil.h"

CUI::CUI() : m_bVisible(false), m_eUIType(EUIType::NONE), m_eUIStatus(EUIStatus::IDLE), m_ptDragCursorOrigin{}, m_ptDragUIOrigin{}
{
}

CUI::~CUI()
{
    Release();
}

void CUI::Initialize()
{
    __super::Initialize();
}

void CUI::PostInitialize()
{
    __super::PostInitialize();

    CKeyManager::GetInstance()->m_OnKeyEventTriggered->AddBinding(GetID(), [this](const TKeyEventCtx& Ctx) { OnKeyEventTriggered(Ctx); });
}

void CUI::Release()
{
    CKeyManager::GetInstance()->m_OnKeyEventTriggered->DeleteBinding(GetID());
}

void CUI::Render(HDC hDC)
{
    /* Test Drag Area */
    HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hNullBrush);

    Rectangle(hDC,
        (int)GetPosition().x,
        (int)GetPosition().y,
        (int)GetPosition().x + 100,
        (int)GetPosition().y + 100
    );
    
    SelectObject(hDC, hOldBrush);
}

void CUI::OnKeyEventTriggered(const TKeyEventCtx& Ctx)
{
}

void CUI::OnFocused()
{
    CUIManager::GetInstance()->UpdateUIOrder(this);
}

void CUI::SetDragOrigin(IPoint ptUIPos, IPoint ptCursorPos)
{
    m_ptDragUIOrigin = ptUIPos;
    m_ptDragCursorOrigin = ptCursorPos;
}

bool CUI::IsCursorOnUI(const IPoint& ptCursorPos)
{
    return true;
}

bool CUI::IsValidInput(IPoint ptCursorPos)
{
	if (!IsVisible()) return false;

	if (!IsCursorOnUI(ptCursorPos))
	{
		switch (GetUIStatus())
		{
		case EUIStatus::IDLE:
			return false;
		case EUIStatus::MOVE:
			return true;
		default:
			return false;
		}
	}
}

void CUI::OnMouseEventTriggered(const TMouseEventCtx& Ctx)
{
    /* vCursorPos is screen space (not local) */
    auto [eKey, eKeyState, ptCursorPos] = Ctx;

    if (eKey == EKey::L_CLICK)
    {
        MoveUI(eKeyState, ptCursorPos);
    }
}

void CUI::MoveUI(EKeyState eKeyState, const IPoint& ptCursorPos)
{
    switch (eKeyState)
    {
    case EKeyState::PRESSED:
    case EKeyState::DOUBLE_PRESSED:
    {
        if (/* this is temporary */ MathUtil::IsPointInRect(ptCursorPos, IPoint(GetPosition()), m_vDummyDragArea))
        {
            cout << "[UI]" << magic_enum::enum_name(GetUIType()) << " UI drag start" << endl;
            SetDragOrigin(IPoint(GetPosition()), ptCursorPos);
            SetUIStatus(EUIStatus::MOVE);
        }
        break;
    }
    case EKeyState::HOLD:
    {
        if (GetUIStatus() == EUIStatus::MOVE)
        {
            IPoint ptDragAmount = ptCursorPos - m_ptDragCursorOrigin;
            SetPosition(Vec2(m_ptDragUIOrigin + ptDragAmount));
        }
        break;
    }
    case EKeyState::RELEASED:
    {
        if (GetUIStatus() == EUIStatus::MOVE)
        {
            cout << GetPosition();
            cout << "[UI]" << magic_enum::enum_name(GetUIType()) << " UI drag end" << endl;
            SetUIStatus(EUIStatus::IDLE);
        }
        break;
    }
    default:
        break;
    }
}
