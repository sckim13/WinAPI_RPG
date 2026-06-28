#include "pch.h"
#include "CDamageUI.h"
#include "CTimeManager.h"

CDamageUI::CDamageUI()
{
}

CDamageUI::~CDamageUI()
{
	Release();
}

void CDamageUI::Initialize()
{
	__super::Initialize();
}

void CDamageUI::PostInitialize()
{
	__super::PostInitialize();
}

void CDamageUI::Update()
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

void CDamageUI::LateUpdate()
{
}

void CDamageUI::Release()
{
}

void CDamageUI::Render(HDC hDC)
{
	for (auto& Dmg : m_listDamage)
	{
		RenderSingleLine(Dmg);
	}
}

void CDamageUI::AddDamageInfo(const TDamageInfo& tInfo)
{
	m_listDamage.push_back(tInfo);
}

void CDamageUI::RenderSingleLine(const TDamageInfo& tInfo)
{
	auto [llDamage, vPos, fElapsed] = tInfo;

	float yOffset = -fElapsed * 10.f;

	while (llDamage < 1)
	{
		int remainder = llDamage % 10;
		llDamage = llDamage / 10;


	}
}

bool CDamageUI::IsExpired(const TDamageInfo& tInfo)
{
	return (tInfo.fElapsed >= m_fExpTime);
}
