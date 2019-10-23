#include "Pch.h"
#include "Application.h"

#include "Rosewood/EventSystem/Event.h"
#include "Rosewood/EventSystem/ApplicationEvent.h"
#include "Rosewood/Log.h"
#include "Window.h"

namespace rw
{

	Application::Application()
		: mWindow(nullptr)
		, mIsRunning(false)
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
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		RW_CORE_INFO("{0}", event);
	}

	bool Application::OnWindowClose(const WindowCloseEvent& event)
	{
		mIsRunning = false;
		return true;
	}

}
