#pragma once

#include "CComponent.h"

class CTexture;

class CAnimator : public CComponent
{
public:
	CAnimator();
	~CAnimator();

	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	void Play();

private:
	CTexture* m_pSprite;
	
	int m_iHeight;
	int m_iWidth;
	int m_iFrameSize;
	vector<int> m_iFrameDelay;
	bool m_bLoop;
};

