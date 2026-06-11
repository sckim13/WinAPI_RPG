#include "pch.h"
#include "CSceneManager.h"

CSceneManager* CSceneManager::g_pInst = nullptr;

CSceneManager::CSceneManager() : m_pCurrentScene(nullptr)
{
}

CSceneManager::~CSceneManager()
{
}

void CSceneManager::Initialize()
{
}

void CSceneManager::Update()
{
}
