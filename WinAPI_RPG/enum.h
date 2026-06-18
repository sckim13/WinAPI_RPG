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
	RIGHT
};