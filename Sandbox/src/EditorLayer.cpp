#include "EditorLayer.h"

#include <imgui/imgui.h>
#include "LabCore/ImGui/ImFileDialog.h"

// --- Other Editors --- //
#include "Components/ImageEditor.h"

using namespace LarkinLab;

EditorLayer::EditorLayer() : Layer("EditoryLayer") 
{ 
}

void EditorLayer::OnAttach()
{
	showExplorer = false;
	m_FileDialog = &ifd::FileDialog::Instance();
	// Initialize ImFileDialog Texture functions
	m_FileDialog->CreateTexture = [](uint8_t* data, int w, int h, char fmt) -> void*
	{
		return OpenGLTexture::FileDialogCreateHelper(data, w, h, fmt);
	};

	m_FileDialog->DeleteTexture = [](void* ID)
	{
		OpenGLTexture::FileDialogDestroyHelper(ID);
	};
}


void EditorLayer::OnDetach() {}

void EditorLayer::OnImGuiRender()
{
	static bool dockspaceOpen = true;
	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
	ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// DockSpace
	ImGuiIO& io = ImGui::GetIO();
	ImGuiStyle& style = ImGui::GetStyle();
	float minWinSizeX = style.WindowMinSize.x;
	style.WindowMinSize.x = 370.0f;
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	style.WindowMinSize.x = minWinSizeX;

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			// Disabling fullscreen would allow the window to be moved to the front of other windows, 
			// which we can't undo at the moment without finer window depth/z control.
			//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);1
			if (ImGui::MenuItem("Open")) showExplorer = true;

			if (ImGui::MenuItem("Save")) m_ImageEditor.Save();

			if (ImGui::MenuItem("Save As...")) showSave = true;

			if (ImGui::MenuItem("Exit")) Application::Get().Close();

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			ImGui::Selectable("Show Original Image", &m_ImageEditor.showOriginal);
			ImGui::Selectable("Show Test Image", &m_ImageEditor.showEdit);

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	// Keep file explorer open
	if (showExplorer)	FileBrowser();
	if (showSave)		SaveBrowser();


	m_ImageEditor.OnImGuiRender();


	ImGui::End();
}

void EditorLayer::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(EditorLayer::OnKeyPressed));
}

//------- Event Functions ------//

bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
{
	// Shortcuts
	if (e.GetRepeatCount() > 0)
		return false;

	bool control = Input::IsKeyPressed(KEY_LEFT_CONTROL) || Input::IsKeyPressed(KEY_RIGHT_CONTROL);
	bool shift = Input::IsKeyPressed(KEY_LEFT_SHIFT) || Input::IsKeyPressed(KEY_RIGHT_SHIFT);

	switch (e.GetKeyCode())
	{
	case KEY_N:
	{
		if (control)
			break; // New Image Open Explorer

		break;
	}
	case KEY_S:
	{
		if (control)
			break; //save edited image

		break;
	}
	}

	return true;
}

// -------- Editor GUIs ------- //
void EditorLayer::FileBrowser()
{
	m_FileDialog->Open("TextureOpenDialog", "Open a texture", "Image file (*.tif;*.png;*.jpg;*.jpeg;*.bmp;*.tga){.tif,.png,.jpg,.jpeg,.bmp,.tga},.*");
	if (m_FileDialog->IsDone("TextureOpenDialog")) 
	{
		if (m_FileDialog->HasResult()) 
		{
			std::string path = m_FileDialog->GetResult().u8string();
			m_ImageEditor.LoadImageToEditor(path);
		}
		m_FileDialog->Close();
		showExplorer = false;
	}
}

void EditorLayer::SaveBrowser()
{
	m_FileDialog->Save("SaveFileDialog", "Save file", "Image file (*.tif;*.png;*.jpg;*.jpeg;*.bmp;*.tga){.tif,.png,.jpg,.jpeg,.bmp,.tga},.*");
	if (m_FileDialog->IsDone("SaveFileDialog"))
	{
		if (m_FileDialog->HasResult())
		{
			std::string path = m_FileDialog->GetResult().u8string();
			m_ImageEditor.SaveAs(path);
		}
		m_FileDialog->Close();
		showSave = false;
	}
}
