#pragma once

class CObject;

class CScene
{

public:
	CScene(const wstring& wstr);
	virtual ~CScene();

	virtual void Initialize();
	virtual void Update();
	virtual void Release();

	virtual void Render();

	const wstring& GetName() { return m_strName; }

	void Enter();
	void Exit();

private:
	vector<CObject*> m_vecObject[(UINT)EObjectType::MAX];
	const wstring m_strName;
};

