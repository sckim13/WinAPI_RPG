#pragma once
class ICollide
{
public:
	virtual void OnCollisionBegin(const TCollisionCtx& Ctx) PURE;
	virtual void OnCollision(const TCollisionCtx& Ctx) PURE;
	virtual void OnCollisionEnd(const TCollisionCtx& Ctx) PURE;
};

