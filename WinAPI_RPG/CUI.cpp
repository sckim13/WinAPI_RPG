#include "pch.h"
#include "CUI.h"
#include "CKeyManager.h"
#include "CUIManager.h"
#include "MathUtil.h"

CUI::CUI() : m_bVisible(false), m_vCursorPosCached{}, m_eUIType(EUIType::NONE), m_eUIStatus(EUIStatus::IDLE)
{
}

CUI::~CUI()
{
}

void CUI::Initialize()
{
	CKeyManager::GetInstance()->m_hOnKeyEventTriggered->AddBinding(
		this,
		[this](TKeyEventCtx Ctx) { OnKeyEventTriggered(Ctx); });
}

void CUI::PostInitialize()
{
}

void CUI::Update()
{
}

void CUI::LateUpdate()
{
}

void CUI::Release()
{
}

void CUI::Render(HDC hDC)
{

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

void CUI::OnKeyEventTriggered(TKeyEventCtx Ctx)
{
}

void CUI::OnFocused()
{
	CUIManager::GetInstance()->UpdateUIOrder(this);
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

void CUI::OnMouseEventTriggered(TMouseEventCtx Ctx)
{
    /* vCursorPos is local */
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
            SetCursorPressedPoint(vCursorPos);
            SetUIStatus(EUIStatus::MOVE);
        }
        break;
    }
    case EKeyState::HOLD:
    {
        if (GetUIStatus() == EUIStatus::MOVE)
        {
            SetPosition(GetPosition() + vCursorPos - m_vCursorPosCached);
        }
        break;
    }
    case EKeyState::RELEASED:
    {
        if (GetUIStatus() == EUIStatus::MOVE)
        {
            cout << "[UI]" << magic_enum::enum_name(GetUIType()) << " UI drag end" << endl;
            SetUIStatus(EUIStatus::IDLE);
        }
        break;
    }
    default:
        break;
    }
}
