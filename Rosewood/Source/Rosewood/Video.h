#pragma once

#include "Rosewood/Core.h"

namespace rw
{
	class Window;

	class Video
	{
	public:
		virtual ~Video() {}

		virtual void SetClearColor(unsigned short red, unsigned short green, unsigned short blue) = 0;

		virtual void BeginRender() = 0;
		virtual void EndRender() = 0;

		static Video* CreateVideo(const Window& window);
	};
}