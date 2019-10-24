#pragma once

#include "Rosewood/Core.h"
#include "Rosewood/LayerStack.h"

namespace rw
{
	class Event;
	class WindowCloseEvent;
	class Window;
	class Layer;

	class ROSEWOOD_API Application
	{
	public:
		Application();

		virtual ~Application();

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	private:
		void OnEvent(Event& event);

		bool OnWindowClose(const WindowCloseEvent& event);

		Window* mWindow;

		bool mIsRunning;

		LayerStack mLayerStack;
	};

	// Should be defined on client
	Application* CreateApplication();

}
