#pragma once

class CObject;

class CScene
{

public:
	CScene();
	virtual ~CScene();

	void SetName(const wstring& strName) { m_strName = strName; }
	const wstring& GetName() { return m_strName; }

private:
	vector<CObject*> m_vecObject[(UINT)EGroupType::MAX];
	wstring m_strName;
};

