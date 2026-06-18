#pragma once
#include "CManager.h"

class CScene;

class CSceneManager : public CManager
{
	SINGLETON(CSceneManager);

public:
	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	inline CScene* GetScene() { return m_pCurrentScene; }

private:
	CScene* m_arrScene[(UINT)ESceneType::MAX];
	CScene* m_pCurrentScene;
};

