#pragma once

#ifdef RW_PLATFORM_WINDOWS

extern rw::Application* rw::CreateApplication();

int main(int argc, char** argv)
{
	printf("Entry Point Rosewood Engine!\n");
	rw::Application* app = rw::CreateApplication();
	app->Run();
	delete app;
}

#endif
