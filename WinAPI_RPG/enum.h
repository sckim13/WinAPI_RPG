#pragma once

#include "Third-party/magic_enum.hpp"

enum class EObjectType
{
	DEFAULT,
	PLAYER,
	MONSTER,
	NPC,
	ITEM,
	SKILL,
	MAP,
	FOOTHOLD,

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

enum class ESkillType
{
	PASSIVE_NONE,
	PASSIVE_MAX,

	ACTIVE_NONE,
	HITSCAN,
	PROJECTILE,
	SUMMON,
	ACTIVE_MAX,
};

enum class EEventType
{
	NONE,

	UI_NONE,
	UI_INVENTORY,
	UI_QUEST,
	UI_EQUIPMENT,
	UI_STATUS,
	UI_SKILL,
	UI_MAX,

	MOUSE_NONE,
	MOUSE_L_CLICK,
	MOUSE_R_CLICK,
	MOUSE_M_CLICK,
	MOUSE_MAX,

	SKILL_NONE,
	SKILL_DEFAULT,
	SKILL_MAX,

	NPC,

	PICKITEM,

};

enum class EKeyState
{
	NONE,
	PRESSED,
	DOUBLE_PRESSED,
	HOLD,
	RELEASED,
};

enum class EKey
{
	// Alphabet Layer
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	COMMA,
	DOT,
	SLASH,
	COLON,
	QUOTE,
	LBRACKET,
	RBRACKET,

	// Upper Number Layer
	TILDE,
	N0,
	N1,
	N2,
	N3,
	N4,
	N5,
	N6,
	N7,
	N8,
	N9,
	MINUS,
	PLUS,

	// Function Key Layer
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,

	// Arrow Key
	LEFT,
	RIGHT,
	UP,
	DOWN,

	// Peripheral
	ESCAPE,
	TAB,
	CAPSLOCK,
	SHIFT,
	CTRL,
	ALT,
	SPACE,
	ENTER,
	RSLASH,
	BACKSPACE,

	// Arrow Upper Layer
	PRINTSCREEN,
	SCROLLLOCK,
	PAUSELOCK,
	INSERT,
	HOME,
	PAGEUP,
	DELETEKEY,
	END,
	PAGEDOWN,

	// Mouse
	L_CLICK,
	R_CLICK,
	M_CLICK,

	MAX,
};

enum class EUIType
{
	NONE,
	INVENTORY,
	EQUIPMENT,
};

enum class EUIStatus
{
	IDLE,
	MOVE,
};