#pragma once

#include "CObject.h"

class CPlayer;
class CTextureComponent;

class CScene : public CObject
{

public:
	CScene(const wstring& wstrName, const wstring& wstrBackKey, const wstring& wstrFrontKey);
	virtual ~CScene();

	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	const wstring& GetName() { return m_wstrName; }

	void Enter();
	void Exit();

	void AddObject(CObject* pObject, EObjectType eType);
	void RequestAddObject(CObject* pObject, EObjectType eType);

	IPoint GetMapSize();

private:
	const wstring m_wstrName;
	const wstring m_wstrFrontKey;
	const wstring m_wstrBackKey;
	
	// object list
	list<CObject*> m_listObject[(UINT)EObjectType::MAX];
	queue<CObject*> m_queueObjectCreationRequested[(UINT)EObjectType::MAX];

	// map
	CTextureComponent* m_pTextureFront;
	CTextureComponent* m_pTextureBack;
	int m_iWidth;
	int m_iHeight;

public:
	list<CObject*>* GetObjectList(EObjectType eType) { return &m_listObject[(int)eType]; }

};

