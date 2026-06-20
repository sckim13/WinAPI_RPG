#include "pch.h"
#include "CUIManager.h"
#include "CInventoryUI.h"
#include "CEquipmentUI.h"
#include "CCursor.h"

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

    CUI* pEquipmentUI = CAbstractFactory<CUI, CEquipmentUI>::Create();
    pEquipmentUI->SetPosition(Vec2{ 0.f, 0.f });
    m_mapUI.insert({ L"Equipment", pEquipmentUI });
}

void CUIManager::PostInitialize()
{
}

void CUIManager::Update()
{
    m_pCursor->Update();
}

void CUIManager::LateUpdate()
{
    m_pCursor->LateUpdate();
}

void CUIManager::Release()
{
    Safe_Delete<CCursor*>(m_pCursor);
}

void CUIManager::Render(HDC hDC)
{
    for (auto pair : m_mapUI)
    {
        pair.second->Render(hDC);
    }
    m_pCursor->Render(hDC);
}

CUI* CUIManager::GetUIFromCoordinates(POINT& pt)
{
    // TODO : Get point
    // Find the most upper UI at that point
    // convert to local point of UI
    // 우선은 점의 좌표를 기준으로 UI 사각형들이 점 안에 들어오는지 판별(pq에 push?) 그리고 가장 우선순위 UI를 반환.
    // UI의 좌상단 좌표를 받고, 현재 pt에서 ui pt를 뺴서 로컬 좌표 계산
    // 
    return m_mapUI[L"Inventory"];
}

CUI* CUIManager::GetUI(wstring wstrName)
{
    return m_mapUI[wstrName];
}
