#pragma once

class ICombat
{
public:
	virtual void OnHit(long long llDamage) PURE;
	virtual void OnDead() PURE;
};

