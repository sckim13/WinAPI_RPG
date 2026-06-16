#pragma once

class CObjectBase;

class CScene
{

public:
	CScene(const wstring& wstr);
	virtual ~CScene();

	virtual void Initialize();
	virtual void Update();
	virtual void Release();

	virtual void Render(HDC hDC);

	const wstring& GetName() { return m_strName; }

	void Enter();
	void Exit();

private:
	vector<CObjectBase*> m_vecObject[(UINT)EObjectType::MAX];
	const wstring m_strName;
};

