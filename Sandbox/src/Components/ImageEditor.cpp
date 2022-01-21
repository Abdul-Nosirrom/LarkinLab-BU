#include "llpch.h"

#include "ImageEditor.h"
#include <imgui/imgui.h>

ImageEditor::ImageEditor() 
{
}


void ImageEditor::OnImGuiRender()
{
	if (m_Image != NULL && showOriginal) ShowImage("Original", m_Image);
	if (m_Edit != NULL && showEdit) ShowImage("Edit", m_Edit);

	ImGui::Begin("Image Editor");

	if (m_ImageLoaded) ShowParameters();

	ImGui::End();
}

void ImageEditor::LoadImageToEditor(std::string path)
{
	if (m_Image != NULL) delete(m_Image);
	if (m_Edit != NULL) delete(m_Edit);
	m_Image = new OpenCVImage(path);
	m_Edit = new OpenCVImage(path);
	m_ImagePath = path;
	m_ImageLoaded = true;
}

void ImageEditor::ApplyEdits()
{

}

void ImageEditor::ShowImage(const char* window, OpenCVImage* image)
{
	ImGui::Begin(window);
	ImVec2 wsize = ImGui::GetWindowSize();
	// Texture loading
	ImGui::Image((void*)(intptr_t)image->GetTexture()->GetTextureID(), ImVec2(image->GetTexture()->GetWidth(), image->GetTexture()->GetHeight()));
	ImGui::End();
}

void ImageEditor::ShowParameters()
{
	ImGui::SliderInt("Gaussian Blur", &m_GaussBlur, 0, 101);
	ImGui::SliderInt("Entre", &m_Entre, 0, 100);
	ImGui::SliderInt("threshold", &m_Threshold, 0, 200);
	ImGui::SliderInt("threshold center", &m_ThreshCenter, 0, 200);
	ImGui::SliderInt("canny thresh", &m_CannyThresh, 0, 200);
}