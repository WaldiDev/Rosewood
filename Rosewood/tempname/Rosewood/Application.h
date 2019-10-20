#pragma once

#include "Core.h"

namespace rw
{
	class ROSEWOOD_API Application
	{
	public:
		Application();

		virtual ~Application();

		void Run();

	};

	// Should be defined on client
	Application* CreateApplication();

}
