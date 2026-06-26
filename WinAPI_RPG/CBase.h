#pragma once

class CBase
{
public:
	CBase();
	virtual ~CBase();

	virtual void Initialize() PURE;
	virtual void PostInitialize() PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Release() PURE;

	virtual void Render(HDC hDC) PURE;


protected:

private:
	static INT64 g_ID;
	INT64 m_ID;

public:
	inline const INT64 GetID() const { return m_ID; }
};

