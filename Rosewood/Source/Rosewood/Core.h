#pragma once

#ifdef RW_PLATFORM_WINDOWS
#else
	#error Supports only Windows!
#endif // RW_PLATFORM_WINDOW

#define BIT(x) (1 << x)

#define SAFE_RELEASE(p)	{ if (p) { (p)->Release(); (p)=nullptr; } }