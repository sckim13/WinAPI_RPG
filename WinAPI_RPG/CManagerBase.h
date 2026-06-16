#pragma once
class CManagerBase
{
public:
	virtual void Initialize() PURE;
	virtual void Update() PURE;
	virtual void Release() PURE;

protected:
	CManagerBase();
	virtual ~CManagerBase();
};

