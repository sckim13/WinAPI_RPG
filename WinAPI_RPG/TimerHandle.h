#pragma once

#include <functional>

using namespace std;

struct TTimerCtx
{

public:
	TTimerCtx() : m_fPrevExecutedTime(0.f), m_fDuration(0.f), m_bLoop(false), m_bNoDelay(false), m_F{} {}

	float GetPrevExecutedTime() { return m_fPrevExecutedTime; }
	bool IsLoop() { return m_bLoop; }
	bool IsNoDelay() { return m_bNoDelay; }
	float GetDuration() { return m_fDuration; }

	void SetPrevExecutedTime(float fTime) { m_fPrevExecutedTime = fTime; }
	void SetDuration(float fDuration) { m_fDuration = fDuration; }
	void SetLoop(bool bLoop) { m_bLoop = bLoop; }
	void SetNoDelay(bool bNoDelay) { m_bNoDelay = bNoDelay; }
	void SetF(function<void()> F) { m_F = F; }

	void Execute() { m_F(); }

	bool OnTime(float fTime)
	{
		return fTime > m_fPrevExecutedTime + m_fDuration;
	}

private:
	float m_fPrevExecutedTime;
	float m_fDuration;
	bool m_bLoop;
	bool m_bNoDelay;
	function<void()> m_F;
};


struct TTimerHandle
{
	friend class CTimerManager;

public:
	TTimerHandle() : m_ID(-1) {}
	TTimerHandle(const TTimerHandle&) = delete;
	TTimerHandle& operator=(const TTimerHandle&) = delete;

private:
	INT64 m_ID;
};

