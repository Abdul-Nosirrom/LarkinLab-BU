#pragma once

#include "LarkinLab.h"

class EditorLayer : public LarkinLab::Layer
{
public:
	EditorLayer();
	virtual ~EditorLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnImGuiRender() override;
	void OnEvent(LarkinLab::Event& e) override;
private:
	bool OnKeyPressed(LarkinLab::KeyPressedEvent& e);
	void FileBrowser();

	ImGui::FileBrowser m_fileDialog;
	LarkinLab::OpenGLTexture* m_Tex;
	bool showExplorer;
	std::string imagePath;
};

