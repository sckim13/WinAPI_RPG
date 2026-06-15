#pragma once

class CScene;

class CSceneManager
{
	SINGLETON(CSceneManager);

public:
	void Initialize();
	void Update();
	void Render();

	inline CScene* GetScene() { return m_pCurrentScene; }

private:
	CScene* m_arrScene[(UINT)ESceneType::MAX];
	CScene* m_pCurrentScene;
};

