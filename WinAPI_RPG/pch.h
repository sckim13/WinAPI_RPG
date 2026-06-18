#pragma once

// System Headers
#include <cassert>
#include <stdio.h>
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <filesystem>
#include <map>
#include <functional>
#include <Windows.h>


// User Defined Headers
#include "Define.h"
#include "Enum.h"
#include "Memory.h"
#include "Constant.h"
#include "Vec2.h"
#include "Mat3.h"
#include "CAbstractFactory.h"
#include "EventContext.h"

// GDI
#pragma comment(lib, "Msimg32.lib")

// GDI+
#include <gdiplus.h>
#pragma comment (lib, "Gdiplus.lib")


// Memory Leakage Inspection
#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif
#endif
// End Memory Leakage Inspection

using namespace Gdiplus;
using namespace std;

/*

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	virtual void Render() override;

	virtual void Initialize();
	virtual void Update();
	virtual void Release();

	virtual void Render();

*/

