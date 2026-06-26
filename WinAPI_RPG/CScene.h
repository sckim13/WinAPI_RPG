#pragma once

#include "CObject.h"

class CPlayer;

class CScene : public CObject
{

public:
	CScene(const wstring& wstr);
	virtual ~CScene();

	virtual void Initialize() override;
	virtual void Initialize(CPlayer* pPlayer);
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	const wstring& GetName() { return m_strName; }

	void Enter();
	void Exit();

	void AddObject(CObject* pObject, EObjectType eType);

private:
	vector<CObject*> m_vecObject[(UINT)EObjectType::MAX];
	const wstring m_strName;
};

