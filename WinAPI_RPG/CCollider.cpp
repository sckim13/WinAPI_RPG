#include "pch.h"
#include "CCollider.h"
#include "CTransform.h"
#include "CObject.h"
#include "CEventHandle.h"
#include "EventContext.h"

INT32 CCollider::g_ID = 0;

CCollider::CCollider() : m_pTransform(nullptr), m_iCollisionCount(0), m_rcCollision{}, m_ID(++g_ID), m_hOnCollisionBegin(nullptr)
{
}

CCollider::~CCollider()
{
	Release();
}

void CCollider::Initialize()
{
	m_pTransform = new CTransform;
	m_hOnCollisionBegin = new CEventHandle<TCollisionCtx>;
	m_hOnCollisionEnd = new CEventHandle<TCollisionCtx>;
}

void CCollider::PostInitialize()
{
}

void CCollider::Update()
{
	// SetPosition(m_pOwner->GetPosition());
}

void CCollider::LateUpdate()
{
	/* follow the owner position */
	CObject* pOwner = GetOwner();
	assert(pOwner);
	
	Vec2 vPos = pOwner->GetTransform()->GetPosition();
	GetTransform()->SetPosition(vPos);
	
	UpdateRect();
}

void CCollider::Release()
{
	Safe_Delete<CTransform*>(m_pTransform);
	Safe_Delete<CEventHandle<TCollisionCtx>*>(m_hOnCollisionBegin);
}

void CCollider::Render(HDC hDC)
{
	#ifdef _DEBUG
	if (!IsEnabled()) return;
	COLORREF rgb = (m_iCollisionCount > 0) ? RGB(255, 0, 0) : RGB(0, 255, 0);
	HPEN hGreenPen = CreatePen(PS_SOLID, 1, rgb);
	HPEN hPrevPen = (HPEN)SelectObject(hDC, hGreenPen);
	
	HBRUSH hEmptyBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(hDC, hEmptyBrush);

	SetBkMode(hDC, TRANSPARENT);

	Vec2 vPos = GetTransform()->GetPosition();
	Rectangle(hDC,
		m_rcCollision.left,
		m_rcCollision.top,
		m_rcCollision.right,
		m_rcCollision.bottom
	);

	SelectObject(hDC, hPrevPen);
	SelectObject(hDC, hPrevBrush);
	DeleteObject(hGreenPen);
	#endif
}

void CCollider::OnCollisionBegin(CCollider* pCounterPart)
{
	++m_iCollisionCount;
	m_vecColliding.push_back(pCounterPart);

	m_hOnCollisionBegin->Broadcast(TCollisionCtx{pCounterPart});
}

void CCollider::OnCollision(CCollider* pCounterPart)
{
	CObject* pObject = GetOwner();
}

void CCollider::OnCollisionEnd(CCollider* pCounterPart)
{
	auto iter = find(m_vecColliding.begin(), m_vecColliding.end(), pCounterPart);
	assert(iter != m_vecColliding.end());

	m_vecColliding.erase(iter);
	--m_iCollisionCount;

	m_hOnCollisionEnd->Broadcast(TCollisionCtx{ pCounterPart });
}

void CCollider::UpdateRect()
{
	Vec2 vPos = GetTransform()->GetPosition();
	m_rcCollision.left = (int)vPos.x - 30;
	m_rcCollision.right = (int)vPos.x + 30;
	m_rcCollision.top = (int)vPos.y - 30;
	m_rcCollision.bottom = (int)vPos.y + 30;
}
