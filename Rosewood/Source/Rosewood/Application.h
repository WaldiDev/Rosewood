#pragma once

#include "Rosewood/Core.h"
#include "Rosewood/LayerStack.h"

namespace rw
{
	class Event;
	class WindowCloseEvent;
	class Window;
	class Video;
	class Layer;
	class InputMapper;

	class Application
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

		void TestAction();

		void AnotherTestAction();

		Window* mWindow;

		Video* mVideo;

		InputMapper* mInputMapper;

		bool mIsRunning;

		LayerStack mLayerStack;

		unsigned int mVertexArray;
		unsigned int mVertexBuffer;
		unsigned int mIndexBuffer;
	};

	// Should be defined on client
	Application* CreateApplication();

}
