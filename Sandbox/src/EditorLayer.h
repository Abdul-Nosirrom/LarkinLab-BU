#pragma once

#include "LarkinLab.h"

#include "OpenCV/OpenCVImage.h"
#include "Components/ImageEditor.h"


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
	void SaveBrowser();
	void SaveFile();

	ifd::FileDialog* m_FileDialog;
	bool showExplorer = false;
	bool showSave = false;

	// Editors
	ImageEditor m_ImageEditor;
};

