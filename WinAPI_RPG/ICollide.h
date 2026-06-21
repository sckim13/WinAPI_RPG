#pragma once
class ICollide
{
public:
	virtual void OnCollisionBegin(TCollisionCtx Ctx) PURE;
	virtual void OnCollision(TCollisionCtx Ctx) PURE;
	virtual void OnCollisionEnd(TCollisionCtx Ctx) PURE;
};

