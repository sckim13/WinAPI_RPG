#pragma once

enum class EObjectType
{
	DEFAULT,
	PLAYER,
	MONSTER,
	ITEM,

	MAX,
};

enum class ESceneType
{
	START,
	STAGE_01,
	STAGE_02,
	END,

	MAX,
};

enum class EPlayerAnim
{
	STAND,
	ALERT,
	WALK,
	SHOOT,
	CROUCH,
	CROUCH_ATTACK,
	FLY,
	JUMP,
	SIT,
	LADDER,
	ROPE,
};

enum class EPlayerState
{
	IDLE,
	WALK,
	JUMP,
	ATTACK,
	HIT,
	DEAD,
};

enum class EMonsterState
{
	IDLE,
	PATROL,
	CHASE,
	ATTACK,
	HIT,
	DEAD,
};

enum class EPoseDirection
{
	LEFT,
	RIGHT,
};

enum class EInventoryTab
{
	EQUIP,
	CONSUME,
	MISC,
	SETUP,

	MAX,
};

enum class EItemType
{
	EQUIP,
	CONSUME,
	MISC,
	SETUP,
};

enum class EEquipSlot
{
	HEAD,
	TOP,
	BOTTOM,
	GLOVES,
	SHOES,
	CAPE,
	SHOULDER,

	WEAPON,
	SUBWEAPON,
	EMBLEM,

	FACE,
	EYES,
	EAR1,
	EAR2,
	BELT,
	RING1,
	RING2,
	RING3,
	RING4,

	BADGE,
	POCKET,
	MEDAL,

	HEART,
	ANDRIOID,

	MAX,

};