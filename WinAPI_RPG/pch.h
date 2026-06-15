#pragma once

using namespace std;

// System Headers
#include <cassert>
#include <windows.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include <map>

// User Defined Headers
#include "define.h"
#include "struct.h"
#include "enum.h"
#include "memory.h"
#include "constant.h"
#include "Vec2.h"
#include "Mat3.h"


// library
#pragma comment(lib, "Msimg32.lib")


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