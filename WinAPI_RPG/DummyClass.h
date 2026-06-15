#pragma once
#include "CObject.h"
class DummyClass :
    public CObject
{
    // Inherited via CObject
    void Initialize() override;
    void Update() override;
    void Release() override;
    void Render(HDC hDC) override;
};

