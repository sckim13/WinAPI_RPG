#include "pch.h"
#include "CBase.h"

INT64 CBase::g_ID = 0;

CBase::CBase() : m_ID(++g_ID)
{
}

CBase::~CBase()
{
}
