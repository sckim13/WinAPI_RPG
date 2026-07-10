#include "pch.h"
#include "CCollider.h"
#include "CTransform.h"
#include "CObject.h"
#include "EventContext.h"
#include "CCameraManager.h"

CCollider::CCollider() : m_iCollisionCount(0), m_rcCollision{}, m_OnCollisionBegin(nullptr), m_vSize{30.f, 30.f}
{
}

CCollider::~CCollider()
{
	Release();
}

void CCollider::Initialize()
{
	m_OnCollisionBegin = new CEventDelegate<TCollisionCtx>;
	m_OnCollisionEnd = new CEventDelegate<TCollisionCtx>;
}

void CCollider::PostInitialize()
{
}

void CCollider::Update()
{
	assert(GetOwner());
	
	/* follow the owner position */
	Vec2 vPos = GetOwner()->GetTransform()->GetPosition();
	GetTransform()->SetPosition(vPos);
	
	UpdateRect();
}

void CCollider::LateUpdate()
{
}

void CCollider::Release()
{
	Safe_Delete<CEventDelegate<TCollisionCtx>*>(m_OnCollisionBegin);
	Safe_Delete<CEventDelegate<TCollisionCtx>*>(m_OnCollisionEnd);
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
	IPoint ptScroll = CCameraManager::GetInstance()->GetScroll();
	
	Rectangle(hDC,
		m_rcCollision.left + ptScroll.x,
		m_rcCollision.top + ptScroll.y,
		m_rcCollision.right + ptScroll.x,
		m_rcCollision.bottom + ptScroll.y
	);

	SelectObject(hDC, hPrevPen);
	SelectObject(hDC, hPrevBrush);
	DeleteObject(hGreenPen);
	#endif
}

void CCollider::OnCollisionBegin(const TCollisionCtx& Ctx)
{
	auto [pCounterPart] = Ctx;
	++m_iCollisionCount;
	m_vecColliding.push_back(pCounterPart);

	m_OnCollisionBegin->Broadcast(TCollisionCtx{pCounterPart});
}

void CCollider::OnCollision(const TCollisionCtx& Ctx)
{
	auto [pCounterPart] = Ctx;
}

void CCollider::OnCollisionEnd(const TCollisionCtx& Ctx)
{
	auto [pCounterPart] = Ctx;
	auto iter = find(m_vecColliding.begin(), m_vecColliding.end(), pCounterPart);
	assert(iter != m_vecColliding.end());

	m_vecColliding.erase(iter);
	--m_iCollisionCount;

	m_OnCollisionEnd->Broadcast(TCollisionCtx{ pCounterPart });
}

void CCollider::UpdateRect()
{
	Vec2 vPos = GetTransform()->GetPosition();
	m_rcCollision.left = (int)vPos.x - m_vSize.x / 2;
	m_rcCollision.right = (int)vPos.x + m_vSize.x / 2;
	m_rcCollision.top = (int)vPos.y - m_vSize.y / 2;
	m_rcCollision.bottom = (int)vPos.y + m_vSize.y / 2;
}
