#pragma once

#ifdef LL_PLATFORM_WINDOWS
	#ifdef LL_BUILD_DLL
		#define LL_API __declspec(dllexport)
	#else
		#define LL_API __declspec(dllimport)
	#endif
#endif 

#ifdef LL_ENABLE_ASSERTS
	#define LL_ASSERT(x,...) { if(!(x)) { LL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define LL_CORE_ASSERT(x,...) { if(!(x)) { LL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else 
	#define LL_ASSERT(x,...)
	#define LL_CORE_ASSERT(x,...)
#endif

#define BIT(x) (1 << x)

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
