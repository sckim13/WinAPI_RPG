#pragma once
#include "CSkill.h"
class CPassiveSkill :
    public CSkill
{
public:
    virtual void Execute() PURE;
};

