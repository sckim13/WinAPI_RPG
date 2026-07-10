#pragma once

#include "pch.h"

struct TDamageInfo
{
	long long llDamage;
	Vec2 vPos;
	float fElapsed;
};

struct TTextureInfo
{
	wstring wstrKey;
	ETextureType eType;
	wstring wstrPath;
};

struct TFootholdInfo
{	
	int iID;
	IPoint ptLeft;
	IPoint ptRight;
	int iLeftID; // Left linked foothold ID
	int iRightID; // Right linked foothold ID
	bool bIsVertical;
};

struct TLadderInfo
{
	IPoint ptBottom;
	IPoint ptTop;
	bool bIsLadder; // if false, rope
};

struct TSceneInfo
{
	wstring wstrName;
	wstring wstrBackKey; // texture key
	wstring wstrFrontKey; // texture key
};

struct TFrameInfo
{
	int iFrame;
	float iDelay; // ms
};

struct TAnimationInfo
{
	wstring wstrName;
	vector<TFrameInfo> vecFrameInfo;
	int iNumFrame;
	IPoint Size; // frame size
	IPoint Origin;
};

struct TSkillInfo
{
	wstring wstrName;
	ESkillType eSkillType;
};

struct TCursorUIInteractionInfo
{
	bool bIsCursorInUI;
	EKeyState eCursorState;
};