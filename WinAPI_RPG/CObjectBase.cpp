#include "pch.h"
#include "CObjectBase.h"
#include "CCollider.h"

CObjectBase::CObjectBase() : m_pOwner(nullptr)
{
}

CObjectBase::~CObjectBase()
{
}

void CObjectBase::Render(HDC hDC)
{
}
