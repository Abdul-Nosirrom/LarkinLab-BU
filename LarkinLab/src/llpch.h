#pragma once

#define NOMINMAX // Defined as errors caused with windows.h if using std::max
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#ifdef LL_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

