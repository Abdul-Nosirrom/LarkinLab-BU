#pragma once

#ifdef LL_PLATFORM_WINDOWS
	#ifdef LL_BUILD_DLL
		#define LL_API __declspec(dllexport)
	#else
		#define LL_API __declspec(dllimport)
	#endif
#endif 