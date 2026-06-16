#pragma once
#include "CManagerBase.h"

class CScene;

class CSceneManager : public CManagerBase
{
	SINGLETON(CSceneManager);

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	void Render(HDC hDC);

	inline CScene* GetScene() { return m_pCurrentScene; }

private:
	CScene* m_arrScene[(UINT)ESceneType::MAX];
	CScene* m_pCurrentScene;
};

