#pragma once
#include "CManagerBase.h"

class CSaveManager : public CManagerBase
{
	SINGLETON(CSaveManager);

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

private:

};

