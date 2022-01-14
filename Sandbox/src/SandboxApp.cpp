#include <LarkinLab.h>

#include "imgui.h"

class ExampleLayer : public LarkinLab::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{

	}

	virtual void OnImGuiRender() override 
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello world!");
		ImGui::End();
	}

	void OnEvent(LarkinLab::Event& event) override
	{
		if (event.GetEventType() == LarkinLab::EventType::KeyPressed)
		{
			LarkinLab::KeyPressedEvent& e = (LarkinLab::KeyPressedEvent&)event;
			LL_TRACE("{0}", (char)e.GetKeyCode());
		}
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