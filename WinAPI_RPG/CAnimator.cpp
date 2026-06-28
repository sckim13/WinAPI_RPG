#include "pch.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CResourceManager.h"
#include "CMainGame.h"
#include "CObject.h"
#include "CTimeManager.h"

CAnimator::CAnimator() : m_iCurrentFrame(0), m_bIsPlaying(false), m_bLoop(false), m_fTimeOnSingleFrame(0.f), m_fSkillInitTime(0.f)
{
}

CAnimator::~CAnimator()
{
}

void CAnimator::Initialize()
{
	m_OnFinished = new CEventDelegate<void>;
}

void CAnimator::PostInitialize()
{
}

void CAnimator::Update()
{
	if (!IsPlaying()) return;

	float DT = CTimeManager::GetInstance()->GetDeltaTime();
	m_fTimeOnSingleFrame += DT;

	if (m_fTimeOnSingleFrame > m_vecFrameDelay[m_iCurrentFrame] / 1000.f)
	{
		float fTimeRemainder = m_fTimeOnSingleFrame - m_vecFrameDelay[m_iCurrentFrame] / 1000.f;
		m_fTimeOnSingleFrame = fTimeRemainder;
		++m_iCurrentFrame;
	}

	if (IsLoop())
	{
		m_iCurrentFrame = (m_iCurrentFrame) % FRAME_COUNT;
	}
	else
	{
		if (m_iCurrentFrame == FRAME_COUNT)
		{
			cout << "FInished Animation" << endl;
			m_OnFinished->Broadcast();
		}
	}

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
			m_iCurrentFrame * FRAME_W, 0,
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
	m_pSprite = CResourceManager::GetInstance()->LoadTexture(wstrName);
	assert(m_pSprite);
}

void CAnimator::Play(bool bLoop)
{
	m_bLoop = bLoop;
	m_bIsPlaying = true;
	m_iCurrentFrame = 0;
	m_fSkillInitTime = CTimeManager::GetInstance()->GetTime();
	m_fTimeOnSingleFrame = 0.f;
}

void CAnimator::Stop()
{
	m_bIsPlaying = false;
	m_iCurrentFrame = 0;
	m_fTimeOnSingleFrame = 0.f;
}
