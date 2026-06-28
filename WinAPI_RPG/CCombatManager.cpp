#include "pch.h"
#include "CCombatManager.h"
#include "CCharacter.h"
#include "CDamageUi.h"
#include "CEffectManager.h"

CCombatManager::CCombatManager()
{
}

CCombatManager::~CCombatManager()
{
}

void CCombatManager::Initialize()
{
}

void CCombatManager::PostInitialize()
{
}

void CCombatManager::Update()
{
}

void CCombatManager::LateUpdate()
{
}

void CCombatManager::Release()
{
}

void CCombatManager::Render(HDC hDC)
{
}

void CCombatManager::RequestDamage(CCharacter* pCharacter, const vector<long long>& vecDamage)
{
	Vec2 vPos = pCharacter->GetPosition();
	// for multi-line hit
	Vec2 yOffset = Vec2{ 0.f, 0.f };
	float fTimeOffset = 0.f;

	for (auto Dmg : vecDamage)
	{
		CEffectManager::GetInstance()->AddDamageInfo(TDamageInfo{ Dmg, vPos + yOffset, fTimeOffset});
		// DMG UI goes upward to screen line by line
		yOffset.y -= 40.f;
		// Give negative time offset to render DMG UI on positive time
		fTimeOffset -= 0.05f;
	}

	long long llSumDamage = 0;
	for (auto& llDamage : vecDamage)
	{
		llSumDamage += llDamage;
	}
	pCharacter->OnHit(llSumDamage);
}
