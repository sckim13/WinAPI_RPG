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
#include <array>
#include <queue>
#include <stack>
#include <random>


// User Defined Headers
#include "Define.h"
#include "Enum.h"
#include "Memory.h"
#include "Constant.h"
#include "Vec2.h"
#include "Mat3.h"
#include "IPoint.h"
#include "CAbstractFactory.h"


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

// User defined header which has namespace issues
#include "CEventDelegate.h"
#include "EventContext.h"
#include "TimerHandle.h"