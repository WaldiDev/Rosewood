#include <Rosewood.h>

class Sandbox : public rw::Application
{
public:
	Sandbox()
	{
	}

	~Sandbox()
	{
	}
};

rw::Application* rw::CreateApplication()
{
	return new Sandbox();
}
