#include "pch.h"
#include "CUI.h"
#include "CKeyManager.h"
#include "CUIManager.h"
#include "MathUtil.h"

CUI::CUI() : m_bVisible(false), m_eUIType(EUIType::NONE), m_eUIStatus(EUIStatus::IDLE), m_vDragCursorOrigin{}, m_vDragUIOrigin{}
{
}

CUI::~CUI()
{
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

void CUI::SetDragOrigin(Vec2 vUIPos, Vec2 vCursorPos)
{
    m_vDragUIOrigin = vUIPos;
    m_vDragCursorOrigin = vCursorPos;
}

bool CUI::IsCursorOnUI(Vec2 vCursorPos)
{
    return true;
}

bool CUI::IsValidInput(Vec2 vCursorPos)
{
	if (!IsVisible()) return false;

	if (!IsCursorOnUI(vCursorPos))
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
    auto [eKey, eKeyState, vCursorPos] = Ctx;

    if (eKey == EKey::L_CLICK)
    {
        MoveUI(eKeyState, vCursorPos);
    }
}

void CUI::MoveUI(EKeyState eKeyState, const Vec2& vCursorPos)
{
    switch (eKeyState)
    {
    case EKeyState::PRESSED:
    case EKeyState::DOUBLE_PRESSED:
    {
        if (/* this is temporary */ MathUtil::IsPointInRect(vCursorPos, Vec2{ 0.f, 0.f }, m_vDummyDragArea))
        {
            cout << "[UI]" << magic_enum::enum_name(GetUIType()) << " UI drag start" << endl;
            SetDragOrigin(GetPosition(), vCursorPos);
            SetUIStatus(EUIStatus::MOVE);
        }
        break;
    }
    case EKeyState::HOLD:
    {
        if (GetUIStatus() == EUIStatus::MOVE)
        {
            Vec2 vDragAmount = vCursorPos - m_vDragCursorOrigin;
            cout << vDragAmount;
            cout << m_vDragUIOrigin << endl;
            SetPosition(m_vDragUIOrigin + vDragAmount);
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
