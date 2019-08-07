#pragma once


#include "target_version.h"
//windows headers


#include <tchar.h>
#include <Windows.h>
#include <windowsx.h>
#include <CommCtrl.h>

//stl headers

#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <map>


#ifndef UNICODE  
typedef std::string tString;
#define to_tstring std::to_string
#else
typedef std::wstring tString;
#define to_tstring std::to_wstring
#endif

