#pragma once

#include "CCharacter.h"
#include "ICombat.h"

class CInventory;
class CEquipment;
class CSkill;

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

	virtual void OnCollisionBegin(TCollisionCtx Ctx) override;
	virtual void OnCollision(TCollisionCtx Ctx) override;
	virtual void OnCollisionEnd(TCollisionCtx Ctx) override;

	void SortCollisionList();

private:
	EPlayerState m_ePlayerState;

	CInventory* m_pInventory;
	CEquipment* m_pEquipment;
	vector<CSkill*> m_vecSkills;

	vector<CObject*> m_vecObjectsOnCollision[(int)EObjectType::MAX];

	virtual void OnKeyEventTriggered(TKeyEventCtx Ctx) override;

public:
	inline CInventory* GetInventory() { return m_pInventory; }
	inline CEquipment* GetEquipment() { return m_pEquipment; }

	// Inherited via ICombat
	void OnHit() override;
	void OnDead() override;
};

