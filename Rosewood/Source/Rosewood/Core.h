#pragma once

#ifdef RW_PLATFORM_WINDOWS
	#ifdef RW_BUILD_DLL
		#define ROSEWOOD_API __declspec(dllexport)
	#else
		#define ROSEWOOD_API __declspec(dllimport)		
	#endif // RW_BUILD_DLL
#else
	#error Supports only Windows!
#endif // RW_PLATFORM_WINDOW

#define BIT(x) (1 << x)

#define SAFE_RELEASE(p)	{ if (p) { (p)->Release(); (p)=nullptr; } }