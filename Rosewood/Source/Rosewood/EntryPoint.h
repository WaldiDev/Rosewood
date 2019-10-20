#pragma once

#ifdef RW_PLATFORM_WINDOWS

extern rw::Application* rw::CreateApplication();

int main(int argc, char** argv)
{
	rw::Log::Init();
	RW_CORE_INFO("Initialized Log!");

	rw::Application* app = rw::CreateApplication();
	app->Run();
	delete app;
}

#endif
