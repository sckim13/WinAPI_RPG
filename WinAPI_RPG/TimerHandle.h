#pragma once

#include <functional>

using namespace std;

struct TTimerCtx
{

public:
	TTimerCtx() : m_lPrevExecutedTime(0), m_fDuration(0), m_bLoop(false), m_bNoDelay(false), m_F{} {}

	DWORD GetPrevExecutedTime() { return m_lPrevExecutedTime; }
	bool IsLoop() { return m_bLoop; }
	bool IsNoDelay() { return m_bNoDelay; }
	float GetDuration() { return m_fDuration; }

	void SetPrevExecutedTime(DWORD dwTime) { m_lPrevExecutedTime = dwTime; }
	void SetDuration(float fDuration) { m_fDuration = fDuration; }
	void SetLoop(bool bLoop) { m_bLoop = bLoop; }
	void SetNoDelay(bool bNoDelay) { m_bNoDelay = bNoDelay; }
	void SetF(function<void()> F) { m_F = F; }

	void Execute() { m_F(); }

	bool OnTime(DWORD dwTime)
	{
		return (float)dwTime / 1000.f > (float)m_lPrevExecutedTime / 1000.f + m_fDuration;
	}

private:
	DWORD m_lPrevExecutedTime;
	float m_fDuration;
	bool m_bLoop;
	bool m_bNoDelay;
	function<void()> m_F;
};


struct TTimerHandle
{
	friend class CTimerMgr;

public:
	TTimerHandle() : m_ID(-1) {}
	TTimerHandle(const TTimerHandle&) = delete;
	TTimerHandle& operator=(const TTimerHandle&) = delete;

private:
	INT64 m_ID;
};

