#include <LarkinLab.h>

#include "imgui.h"
#include "LabCore/ImGui/imfilebrowser.h"

class ExampleLayer : public LarkinLab::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		m_fileDialog.SetTitle("File Explorer");
		m_fileDialog.SetTypeFilters({".tif"});
	}

	void OnUpdate() override
	{

	}

	virtual void OnImGuiRender() override 
	{
		ImGui::Begin("Test");
		if (ImGui::Button("Select Image:"))
		{
			m_fileDialog.Open();
		}
		if (m_fileDialog.HasSelected())
		{
			imagePath = m_fileDialog.GetSelected().string();
			LL_TRACE(imagePath);
			m_fileDialog.ClearSelected();
		}
		m_fileDialog.Display();
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

private:
	ImGui::FileBrowser m_fileDialog;
	bool showExplorer;
	std::string imagePath;

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