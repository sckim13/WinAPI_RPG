#pragma once
#include "CManager.h"

class CPlayer;
class CScene;
class CCursor;

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

	void AddObject(CObject* pObject, EObjectType eType);
	void RequestAddObject(CObject* pObject, EObjectType eType);

private:
	CCursor* m_pCursor;
	CPlayer* m_pPlayer;
	CScene* m_arrScene[(UINT)ESceneType::MAX];
	CScene* m_pCurrentScene;

public:
	inline CPlayer* GetPlayer() { return m_pPlayer; }
	inline CScene* GetScene() { return m_pCurrentScene; }
};

