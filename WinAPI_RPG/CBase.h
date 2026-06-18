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
};

