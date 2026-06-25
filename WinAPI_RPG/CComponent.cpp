#include "pch.h"
#include "CComponent.h"
#include "CObject.h"

CComponent::CComponent() : m_pOwner(nullptr)
{
}

CComponent::~CComponent()
{
}

void CComponent::AttachTo(CObject* pObject)
{
	SetOwner(pObject);
	pObject->AddComponent(this);
}
