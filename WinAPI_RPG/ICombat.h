#pragma once

class ICombat
{
public:
	virtual void OnHit() PURE;
	virtual void OnDead() PURE;
};

