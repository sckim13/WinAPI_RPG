#pragma once

#include "CCharacter.h"
#include "ICombat.h"

class CInventory;
class CEquipment;
class CSkillComponent;

class CPlayer : public CCharacter, public ICombat
{

public:
	CPlayer();
	virtual ~CPlayer();

	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	/* ICollide */
	virtual void OnCollisionBegin(const TCollisionCtx& Ctx) override;
	virtual void OnCollision(const TCollisionCtx& Ctx) override;
	virtual void OnCollisionEnd(const TCollisionCtx& Ctx) override;

	void SortCollisionList();

private:
	EPlayerState m_ePlayerState;

	CInventory* m_pInventory;
	CEquipment* m_pEquipment;
	CSkillComponent* m_pSkillComponent;

	vector<CObject*> m_vecObjectsOnCollision[(int)EObjectType::MAX];

	/* CObject */
	virtual void OnKeyEventTriggered(const TKeyEventCtx& Ctx) override;

public:
	inline CInventory* GetInventory() { return m_pInventory; }
	inline CEquipment* GetEquipment() { return m_pEquipment; }

	virtual void OnHit() override;
	virtual void OnDead() override;
};

