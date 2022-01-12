#include <LarkinLab.h>

class ExampleLayer : public LarkinLab::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		LL_INFO("ExampleLayer::Update");
	}

	void OnEvent(LarkinLab::Event& event) override
	{
		LL_TRACE("{0}", event);
	}

};

class Sandbox : public LarkinLab::Application
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

LarkinLab::Application* LarkinLab::CreateApplication()
{
	return new Sandbox();
}