#include "pch.h"
#include "CMonster.h"
#include "CTransform.h"
#include "CCollider.h"
#include "CResourceManager.h"
#include "CTexture.h"
#include "CPlayer.h"
#include "CEventHandle.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
}

void CMonster::Initialize()
{
	m_pTexture = CResourceManager::GetInstance()->LoadTexture(L"Monster", L"Texture\\Monster.bmp");
	m_pTexture->SetOwner(this);
	m_pCollider = new CCollider;
	m_pCollider->Initialize();
	m_pCollider->SetOwner(this);
	m_pTransform = new CTransform;
	m_pTransform->SetOwner(this);

	/* bind event to collider */
	GetCollider()->m_hOnCollisionEntered->AddBinding(this, [this](tagCollisionContext Ctx) { OnCollisionEntered(Ctx); });
}

void CMonster::PostInitialize()
{
}

void CMonster::Update()
{
}

void CMonster::LateUpdate()
{
	GetCollider()->LateUpdate();
}

void CMonster::Release()
{
}

void CMonster::Render(HDC hDC)
{
	int iWidth = (int)GetTexture()->GetWidth();
	int iHeight = (int)GetTexture()->GetHeight();

	Vec2 vPos = GetTransform()->GetPosition();


	TransparentBlt(
		hDC,
		(int)(vPos.x - (float)(iWidth / 2)),
		(int)(vPos.y - (float)(iHeight / 2)),
		iWidth, iHeight,
		GetTexture()->GetDC(),
		0, 0, iWidth, iHeight,
		RGB(255, 255, 255)
	);

	GetCollider()->Render(hDC);
}

void CMonster::OnCollisionEntered(tagCollisionContext Ctx)
{
	CObject* pObject = Ctx.pCounterPart->GetOwner();

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObject);
	if (!pPlayer) return;

	cout << "Hit by Player" << endl;
}

