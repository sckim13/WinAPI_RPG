#pragma once

#include "CCharacter.h"

class CInventory;
class CEquipment;
class CSkill;

class CPlayer : public CCharacter
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

	void OnCollisionBegin(TCollisionCtx Ctx);
	void OnCollisionEnd(TCollisionCtx Ctx);
	void SortCollisionList();

private:
	EPlayerState m_ePlayerState;

	CInventory* m_pInventory;
	CEquipment* m_pEquipment;
	vector<CSkill*> m_vecSkills;

	vector<CObject*> m_vecObjectsOnCollision[(int)EObjectType::MAX];

public:
	inline CInventory* GetInventory() { return m_pInventory; }
	inline CEquipment* GetEquipment() { return m_pEquipment; }
};

