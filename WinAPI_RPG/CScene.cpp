#include "pch.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CTexture.h"
#include "CPathManager.h"
#include "CMonster.h"

CScene::CScene(const wstring& wstr) : m_strName(wstr)
{
	Initialize();
}

CScene::~CScene()
{
	for (int i = 0; i < (int)EObjectType::MAX; ++i)
	{
		for (auto& pObject : m_vecObject[i])
		{
			Safe_Delete(pObject);
		}
	}
}

void CScene::Initialize()
{
	CPlayer* pPlayer = new CPlayer;
	m_vecObject[(UINT)EObjectType::PLAYER].push_back(pPlayer);
	pPlayer->SetPosition(Vec2{ 400, 300 });
	pPlayer->SetScale(Vec2{ 100, 100 });

	CMonster* pMonsterA = new CMonster;
	m_vecObject[(UINT)EObjectType::MONSTER].push_back(pMonsterA);
	pMonsterA->SetPosition(Vec2{ 100, 100 });
	pMonsterA->SetScale(Vec2{ 70, 70 });
}

void CScene::Update()
{
	for (int i = 0; i < (int)EObjectType::MAX; ++i)
	{
		for (auto& pObject : m_vecObject[i])
		{
			pObject->Update();
		}
	}
}

void CScene::Release()
{
}

void CScene::Render(HDC hDC)
{
	for (int i = 0; i < (int)EObjectType::MAX; ++i)
	{
		for (auto& pObject : m_vecObject[i])
		{
			pObject->Render(hDC);
		}
	}
}

void CScene::Enter()
{

}

void CScene::Exit()
{
	//for (int i = 0; i < (int)EObjectType::MAX; ++i)
	//{
	//	for (auto& pObject : m_vecObject[i])
	//	{
	//		Safe_Delete(pObject);
	//	}
	//}
}
