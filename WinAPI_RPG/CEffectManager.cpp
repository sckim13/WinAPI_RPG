#include "pch.h"
#include "CEffectManager.h"
#include "CResourceManager.h"
#include "CTexture.h"
#include "CTimeManager.h"

vector<wstring> g_DamageName =
{
    L"Damage_Red_Normal_0",
    L"Damage_Red_Normal_1",
    L"Damage_Red_Normal_2",
    L"Damage_Red_Normal_3",
    L"Damage_Red_Normal_4",
    L"Damage_Red_Normal_5",
    L"Damage_Red_Normal_6",
    L"Damage_Red_Normal_7",
    L"Damage_Red_Normal_8",
    L"Damage_Red_Normal_9"
};

CEffectManager::CEffectManager()
{
}

CEffectManager::~CEffectManager()
{
	Release();
}

void CEffectManager::Initialize()
{
    for (int i = 0; i < 10; ++i)
    {
        m_vecDamageTexture[i] = CResourceManager::GetInstance()->LoadTexture(g_DamageName[i]);
    }
}

void CEffectManager::PostInitialize()
{
}

void CEffectManager::Update()
{
    float DT = CTimeManager::GetInstance()->GetDeltaTime();
    for (auto iter = m_listDamage.begin(); iter != m_listDamage.end(); )
    {
        TDamageInfo& Dmg = (*iter);
        Dmg.fElapsed += DT;
        if (IsExpired(Dmg))
        {
            iter = m_listDamage.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}

void CEffectManager::LateUpdate()
{
}

void CEffectManager::Release()
{
}

void CEffectManager::Render(HDC hDC)
{
    for (auto& Dmg : m_listDamage)
    {
        // deliver negative time from combat manager
        if (Dmg.fElapsed >= 0)
        {
            RenderSingleDamage(hDC, Dmg);
        }
    }
}

void CEffectManager::SwtichDamageSkin()
{
}

void CEffectManager::AddDamageInfo(const TDamageInfo& tInfo)
{
    m_listDamage.push_back(tInfo);
}

void CEffectManager::RenderSingleDamage(HDC hDC, const TDamageInfo& tInfo) const
{
    auto [llDamage, vPos, fElapsed] = tInfo;

    float yOffset = -fElapsed * 30.f;

    stack<int> s;
    while (llDamage >= 1)
    {
        int remainder = llDamage % 10;
        llDamage = llDamage / 10;

        s.push(remainder);
    }

    float fNumberSize = 40.f;
    float StartPos = -fNumberSize / 2.f * s.size();
    while (!s.empty())
    {
        m_vecDamageTexture[s.top()]->Render(hDC, vPos.x + StartPos, vPos.y + yOffset);
        s.pop();
        StartPos += fNumberSize;
    }
}

bool CEffectManager::IsExpired(const TDamageInfo& tInfo)
{
    return (tInfo.fElapsed >= m_fExpTime);
}
