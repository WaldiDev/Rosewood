#pragma once

#include "Rosewood/Core.h"

namespace rw
{
	class Window;

	class Video
	{
	public:
		virtual ~Video() {}

		virtual void OnRender() = 0;

		static Video* CreateVideo(const Window& window);
	};
}