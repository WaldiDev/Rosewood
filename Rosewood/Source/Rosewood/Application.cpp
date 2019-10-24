#include "Pch.h"
#include "Application.h"

#include "Rosewood/EventSystem/Event.h"
#include "Rosewood/EventSystem/ApplicationEvent.h"
#include "Rosewood/Log.h"
#include "Rosewood/Layer.h"
#include "Rosewood/Window.h"

namespace rw
{

	Application::Application()
		: mWindow(nullptr)
		, mIsRunning(false)
		, mLayerStack()
	{
		mWindow = Window::RWCreateWindow(WindowDefinition());
		mWindow->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		mIsRunning = true;

		while (mIsRunning)
		{
			mWindow->OnUpdate();

			for (Layer* layer : mLayerStack)
			{
				layer->OnUpdate();
			}
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		mLayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		mLayerStack.PushOverlay(layer);
	}

	void Application::OnEvent(Event& event)
	{
		RW_CORE_INFO("{0}", event);

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		
		// forward events to layers in reversed order, so overlays will recive events first
		for (LayerStackIterater layerIter = mLayerStack.end(); layerIter != mLayerStack.begin(); --layerIter)
		{
			(*layerIter)->OnEvent(event);
			if (event.GetIsHandled())
			{
				break;
			}
		}
	}

	bool Application::OnWindowClose(const WindowCloseEvent& event)
	{
		mIsRunning = false;
		return true;
	}

}
