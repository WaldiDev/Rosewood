#include <Rosewood.h>

class ExampleLayer : public rw::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override
	{

	}

	void OnEvent(rw::Event& event) override
	{

	}
};

class Sandbox : public rw::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	}
};

rw::Application* rw::CreateApplication()
{
	return new Sandbox();
}
