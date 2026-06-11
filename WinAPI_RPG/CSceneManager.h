#pragma once

class CScene;

class CSceneManager
{
	SINGLETON(CSceneManager);

public:
	void Initialize();
	void Update();

private:
	CScene* m_arrScene[(UINT)ESceneType::MAX];
	CScene* m_pCurrentScene;
};

