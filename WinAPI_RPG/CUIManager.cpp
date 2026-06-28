#include "pch.h"
#include "CUIManager.h"
#include "CInventoryUI.h"
#include "CEquipmentUI.h"
#include "CKeyManager.h"
#include "CCursor.h"
#include "CUI.h"
#include "CDamageUI.h"

CUIManager::CUIManager() : m_pCursor(nullptr)
{
}

CUIManager::~CUIManager()
{
}

void CUIManager::Initialize()
{
    m_pCursor = new CCursor;
    m_pCursor->Initialize();

    CUI* pInventoryUI = CAbstractFactory<CUI, CInventoryUI>::Create();
    pInventoryUI->SetPosition(Vec2{ 0.f, 0.f });
    m_mapUI.insert({ L"Inventory", pInventoryUI });
    m_listUI.push_front(pInventoryUI);
    m_umapUI.insert({ pInventoryUI, m_listUI.begin() });

    CUI* pEquipmentUI = CAbstractFactory<CUI, CEquipmentUI>::Create();
    pEquipmentUI->SetPosition(Vec2{ 0.f, 0.f });
    m_mapUI.insert({ L"Equipment", pEquipmentUI });
    m_listUI.push_front(pEquipmentUI);
    m_umapUI.insert({ pEquipmentUI, m_listUI.begin() });

    for (auto pair : m_mapUI)
    {
        pair.second->Initialize();
    }
}

void CUIManager::PostInitialize()
{
    CKeyManager::GetInstance()->m_OnMouseEventTriggered->AddBinding(GetID(), [this](const TMouseEventCtx& Ctx) { OnMouseEventTriggered(Ctx); });

    for (auto pair : m_mapUI)
    {
        pair.second->PostInitialize();
    }
}

void CUIManager::Update()
{
    for (auto pair : m_mapUI)
    {
        pair.second->Update();
    }
    m_pCursor->Update();
}

void CUIManager::LateUpdate()
{
    for (auto pair : m_mapUI)
    {
        pair.second->LateUpdate();
    }
    m_pCursor->LateUpdate();
}

void CUIManager::Release()
{
    for (auto pUI : m_listUI)
    {
        Safe_Delete<CUI*>(pUI);
    }
    Safe_Delete<CCursor*>(m_pCursor);
}

void CUIManager::Render(HDC hDC)
{
    for (auto iter = m_listUI.rbegin(); iter != m_listUI.rend(); ++iter)
    {
        (*iter)->Render(hDC);
    }
    m_pCursor->Render(hDC);
}

CUI* CUIManager::GetUI(wstring wstrName)
{
    return m_mapUI[wstrName];
}


void CUIManager::OnMouseEventTriggered(const TMouseEventCtx& Ctx)
{
    auto [eKey, eKeyState, DummyCursorPos] = Ctx;
    Vec2 vCursorPos = m_pCursor->GetPosition();

    for (auto iter = m_listUI.begin(); iter != m_listUI.end(); )
    {
        CUI* pUI = (*iter);

        if (pUI->IsValidInput(vCursorPos))
        {
            pUI->OnMouseEventTriggered(TMouseEventCtx{eKey, eKeyState, vCursorPos});
            /* Caution!! : Below function causes dangling iter */
            UpdateUIOrder(pUI);
            /* Caution!! : Above function causes dangling iter */
            return;
        }
        else
        {
            ++iter;
        }
    }
    // cout << "[UI Manager] No UI is on the cursor" << endl;
}

void CUIManager::UpdateUIOrder(CUI* pUI)
{
    auto iter = m_umapUI[pUI];
    m_listUI.erase(iter);
    m_listUI.push_front(pUI);
    m_umapUI[pUI] = m_listUI.begin();
}
