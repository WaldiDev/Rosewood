#include "Application.h"

#include "Rosewood/EventSystem/Event.h"
#include "Rosewood/Log.h"
#include "EventSystem/ApplicationEvent.h"

namespace rw
{

	Application::Application()
	{

	}


	Application::~Application()
	{

	}


	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			RW_CORE_WARN(e);
		}

		while (true)
		{
		}
	}
}
