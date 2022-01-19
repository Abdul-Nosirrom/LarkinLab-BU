#include <LarkinLab.h>
#include <LabCore/EntryPoint.h>

#include "EditorLayer.h"



class Sandbox : public LarkinLab::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new EditorLayer());
	}

	~Sandbox()
	{

	}
};

LarkinLab::Application* LarkinLab::CreateApplication()
{
	return new Sandbox();
}


/*
#include "imgui.h"
#include "LabCore/ImGui/imfilebrowser.h"
#include "EditorLayer.h"

class ExampleLayer : public LarkinLab::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		m_fileDialog.SetTitle("File Explorer");
		m_fileDialog.SetTypeFilters({".tif", ".png"});
		m_Tex = new LarkinLab::OpenGLTexture();
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
			DisplayImage(m_fileDialog.GetSelected().string());
		}
		m_fileDialog.Display();
		ImGui::End();
	}

	void DisplayImage(std::string filename)
	{

		imagePath = filename;
		LL_TRACE(imagePath);
		//m_fileDialog.ClearSelected();
		ImGui::BeginChild("Image Render");
		ImVec2 wsize = ImGui::GetWindowSize();
		// Texture loading
		const char* pathCstring = imagePath.c_str();
		bool texAssert = m_Tex->LoadTextureFromFile(pathCstring);
		LL_ASSERT(texAssert, "Image Load Failure");
		//
		ImGui::Image((void*)(intptr_t)m_Tex->GetTextureID(), ImVec2(m_Tex->GetWidth(), m_Tex->GetHeight()));
		ImGui::EndChild();
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
	LarkinLab::OpenGLTexture* m_Tex;
	bool showExplorer;
	std::string imagePath;

};
*/