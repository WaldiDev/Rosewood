#pragma once

#include "Core.h"

namespace rw
{
	class Window;

	class ROSEWOOD_API Application
	{
	public:
		Application();

		virtual ~Application();

		void Run();

	private:
		Window* mWindow;
	};

	// Should be defined on client
	Application* CreateApplication();

}
