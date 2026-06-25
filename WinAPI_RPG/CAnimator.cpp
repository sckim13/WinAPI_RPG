#include "pch.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CResourceManager.h"
#include "CMainGame.h"
#include "CObject.h"

CAnimator::CAnimator() : m_iCurrentIndex(0), m_bIsPlaying(false)
{
}

CAnimator::~CAnimator()
{
}

void CAnimator::Initialize()
{
}

void CAnimator::PostInitialize()
{
}

void CAnimator::Update()
{
	m_iCurrentIndex = (m_iCurrentIndex + 1) % FRAME_COUNT;
}

void CAnimator::LateUpdate()
{
}

void CAnimator::Release()
{
}

void CAnimator::Render(HDC hDC)
{
	if (m_bIsPlaying)
	{
		m_pSprite->Render(hDC,
			GetOwner()->GetPosition().x, GetOwner()->GetPosition().y,
			m_iCurrentIndex * FRAME_W, 0,
			FRAME_W, FRAME_H);
	}

	/*TODO
	
	스킬 컴포넌트, 스킬 오브젝트 분리
	오브젝트는 서로 기본적으로 소유 안하는 구조
	
	각 오브젝트는 컴포넌트 리스트를 내부적으로 보유
	컴포넌트에서 attachTo 등으로 벡터에 등록
	오늘 가기 전에 스킬 키 누르면 연속 애니메이션 나오는거 확인하기
	
	*/
}

void CAnimator::BindTexture(const wstring& wstrName)
{
	m_pSprite = CResourceManager::GetInstance()->LoadTexture(wstrName, L"");
}

void CAnimator::Play()
{
	assert(m_pSprite);

	m_bIsPlaying = true;
	m_iCurrentIndex = 0;
}
