#pragma once

using namespace std;

// System Headers
#include <cassert>
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include <map>


// User Defined Headers
#include "Define.h"
#include "Enum.h"
#include "Memory.h"
#include "Constant.h"
#include "Transform.h"
#include "Vec2.h"
#include "Mat3.h"

// GDI
#pragma comment(lib, "Msimg32.lib")

// GDI+
//	source : https://stackoverflow.com/questions/45957830/gdipluspath-throws-ambiguous-byte-for-cstddef-and-rpcndr-h
//  global compilation flag configuring windows sdk headers
//  preventing inclusion of min and max macros clashing with <limits>
#define NOMINMAX 1

//  override byte to prevent clashes with <cstddef>
#define byte win_byte_override

#include <Windows.h> // gdi plus requires Windows.h
// ...includes for other windows header that may use byte...

//  Define min max macros required by GDI+ headers.
#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#else
#error max macro is already defined
#endif
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#else
#error min macro is already defined
#endif

#include <gdiplus.h>

//  Undefine min max macros so they won't collide with <limits> header content.
#undef min
#undef max

//  Undefine byte macros so it won't collide with <cstddef> header content.
#undef byte

#pragma comment (lib, "Gdiplus.lib")
using namespace Gdiplus;


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