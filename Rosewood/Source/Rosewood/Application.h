#pragma once

#include "Core.h"

namespace rw
{
	class Event;
	class WindowCloseEvent;
	class Window;

	class ROSEWOOD_API Application
	{
	public:
		Application();

		virtual ~Application();

		void Run();

	private:
		void OnEvent(Event& event);

		bool OnWindowClose(const WindowCloseEvent& event);

		Window* mWindow;

		bool mIsRunning;
	};

	// Should be defined on client
	Application* CreateApplication();

}
