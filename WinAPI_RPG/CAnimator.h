#pragma once

#include "CComponent.h"

class CTexture;

class CAnimator : public CComponent
{
public:
	CAnimator();
	virtual ~CAnimator();

	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	void BindTexture(const wstring& wstrName);
	void Play(bool bLoop);
	void Stop();

	CEventDelegate<void>* m_OnFinished;

private:
	CTexture* m_pSprite;
	
	const int FRAME_W = 580;
	const int FRAME_H = 348;
	const int FRAME_COUNT = 11;
	const int FRAME_DELAY = 90; // ms
	vector<float> m_vecFrameDelay = {90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90};
	//const int FRAME_W = 250;
	//const int FRAME_H = 250;
	//const int FRAME_COUNT = 4;
	//const int FRAME_DELAY = 90; // ms

	bool m_bIsPlaying;
	int m_iCurrentFrame;
	// nt m_iHeight;
	// int m_iWidth;
	// int m_iFrameSize;
	// float m_iFrameDelay;
	bool m_bLoop;
	
	float m_fSkillInitTime;
	float m_fTimeOnSingleFrame;

public:
	bool IsLoop() { return m_bLoop; }
	bool IsPlaying() { return m_bIsPlaying; }
	int GetCurrentFrame() { return m_iCurrentFrame; }
	Vec2 GetFrameSize() { return Vec2{FRAME_W, FRAME_H}; }
};

