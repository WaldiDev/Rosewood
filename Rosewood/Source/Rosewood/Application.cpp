#include "Pch.h"
#include "Application.h"

#include "Rosewood/EventSystem/Event.h"
#include "Rosewood/EventSystem/ApplicationEvent.h"
#include "Rosewood/Log.h"
#include "Rosewood/Layer.h"
#include "Rosewood/Window.h"
#include "Rosewood/Video.h"
#include "Rosewood/InputSystem/InputMapper.h"

namespace rw
{

	Application::Application()
		: mWindow(nullptr)
		, mVideo(nullptr)
		, mIsRunning(false)
		, mLayerStack()
	{

		mInputMapper = new InputMapper();

		mWindow = Window::RWCreateWindow(WindowDefinition());
		mWindow->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
		mWindow->SetInputMapper(mInputMapper);

		mVideo = Video::CreateVideo(*mWindow);

		mInputMapper->AddActionNameToKeyBinding("TestAction", { KeyboardKey(VirtualKey::RW_VK_Q), KeyboardKey(VirtualKey::RW_VK_W), KeyboardKey(VirtualKey::RW_VK_E) });
		mInputMapper->AddActionNameToKeyBinding("AnotherTestAction", { { KeyboardKey(VirtualKey::RW_VK_E) } });

		InputContext& myContext = mInputMapper->CreateNewContext();		
		myContext.AddBinding("TestAction", InputState::Repeated, std::bind(&Application::TestAction, this));
		myContext.AddBinding("AnotherTestAction", InputState::Pressed, std::bind(&Application::AnotherTestAction, this));
	}

	Application::~Application()
	{
		delete mVideo;
		delete mWindow;
	}

	void Application::Run()
	{
		mIsRunning = true;

		while (mIsRunning)
		{
			mWindow->OnUpdate();
			mInputMapper->Dispatch();

			for (Layer* layer : mLayerStack)
			{
				layer->OnUpdate();
			}

			mVideo->BeginRender();

			// Start rendering objects here

			mVideo->EndRender();
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
		LayerStackIterater layerIter = mLayerStack.end();
		while (layerIter != mLayerStack.begin())
		{
			--layerIter;
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

	void Application::TestAction()
	{
		RW_CORE_INFO("TestAction");
	}

	void Application::AnotherTestAction()
	{
		RW_CORE_INFO("AnotherTestAction");
	}

}
