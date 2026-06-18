#pragma once

#include "CComponent.h"

class CResource : public CComponent
{
public:
	CResource();
	virtual ~CResource() PURE;

	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	inline void SetKey(const wstring& strKey) { m_strKey = strKey; }
	inline void SetRelativePath(const wstring& strRelPath) { m_strRelPath = strRelPath; }
	
	inline wstring& GetKey() { return m_strKey; }
	inline wstring& GetRelativePath() { return m_strRelPath; }

private:
	wstring m_strKey;
	wstring m_strRelPath;
};

