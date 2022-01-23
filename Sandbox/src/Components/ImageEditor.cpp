#include "llpch.h"

#include "ImageEditor.h"
#include <imgui/imgui.h>

#include <math.h>

#include <opencv2/opencv.hpp>

ImageEditor::ImageEditor() 
{
}


void ImageEditor::OnImGuiRender()
{
	if (m_Image != NULL && showOriginal) ShowImage("Original", m_Image);
	if (m_Edit != NULL && showEdit) ShowImage("Edit", m_Edit);

	ImGui::Begin("Image Editor");

	if (m_ImageLoaded) 
	{
		ShowParameters();
		ApplyEdits();
	}

	ImGui::End();
}

void ImageEditor::Save()
{
	m_Edit->SaveImage(m_ImagePath);
}

void ImageEditor::SaveAs(std::string path)
{
	m_Edit->SaveImage(path);
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
	// -- Gaussian Blur -- //
	if (m_GaussBlur % 2 == 0) m_GaussBlur += 1;

	if (m_GaussBlurOld != m_GaussBlur) 
		m_Edit->GaussianBlur(m_GaussBlur);

	m_GaussBlurOld = m_GaussBlur;
	//////////////////////////
	// -- Find Circles  -- //
	if (m_findCircles)
	{
		//m_Edit->FindCircles(m_Entre, m_Threshold, m_ThreshCenter); // CRASHES
		m_findCircles = false;
	}
	//////////////////////////
	// -- Find Contours -- //
	if (m_findContours)
	{
		m_Edit->FindCountours(m_CannyThresh);
		m_findContours = false;
	}
}

void ImageEditor::ShowImage(const char* window, OpenCVImage* image)
{
	// Maintain aspect ratio but fit to window size
	float AR = (float)image->GetTexture()->GetWidth() / (float)image->GetTexture()->GetHeight();

	ImGui::Begin(window);
	// Maintain aspect ratio
	ImVec2 wsize = ImGui::GetWindowSize();
	float minSide = MIN(wsize.x, wsize.y);
	ImVec2 arsize = ImVec2(minSide * AR, minSide);
	// Texture loading
	ImGui::Image((void*)(intptr_t)image->GetTexture()->GetTextureID(), arsize);
	ImGui::End();
}

void ImageEditor::ShowParameters()
{
	if (ImGui::CollapsingHeader("Color Editors"))
	{
		if (ImGui::Button("Change to Grayscale")) m_Edit->Grayscale();
		ImGui::SliderInt("Gaussian Blur", &m_GaussBlur, 0, 101); 
	}
	ImGui::NewLine();
	ImGui::Separator();

	if (ImGui::CollapsingHeader("Contour Detection"))
	{
		ImGui::SliderInt("Contour Threshold", &m_CannyThresh, 0, 200); 
		if (ImGui::Button("Find Contours", ImVec2(100, 20))) m_findContours = true;
	}


	ImGui::NewLine();
	ImGui::Separator();
	if (ImGui::CollapsingHeader("Blob Detection"))
	{
		ImGui::SliderFloat("Min Threshold", &m_Edit->blobDetectionParams.minThreshold, 10, m_Edit->blobDetectionParams.maxThreshold);
		ImGui::SliderFloat("Max Threshold", &m_Edit->blobDetectionParams.maxThreshold, m_Edit->blobDetectionParams.minThreshold, 200);
		ImGui::Separator();
		ImGui::Selectable("Filter by Area", &m_Edit->blobDetectionParams.filterByArea, 0, ImVec2(130, 15));
		if (m_Edit->blobDetectionParams.filterByArea)
		{
			ImGui::SliderFloat("Minimum Area", &m_Edit->blobDetectionParams.minArea, 0.001, 1);
		}

		ImGui::Separator();
		ImGui::Selectable("Filter by Convexity", &m_Edit->blobDetectionParams.filterByConvexity, 0, ImVec2(130, 15));
		if (m_Edit->blobDetectionParams.filterByConvexity)
		{
			ImGui::SliderFloat("Minimum Convexity", &m_Edit->blobDetectionParams.minConvexity, 0.001, 2);
		}

		ImGui::Separator();
		ImGui::Selectable("Filter by Inertia", &m_Edit->blobDetectionParams.filterByInertia, 0, ImVec2(130, 15));
		if (m_Edit->blobDetectionParams.filterByInertia)
		{
			ImGui::SliderFloat("Minimum Inertia", &m_Edit->blobDetectionParams.minInertiaRatio, 0.001, 1);
		}
		ImGui::Separator();
		if (ImGui::Button("Initialize Blob Detection")) m_Edit->FindBlobs();
	}
	ImGui::NewLine();
	ImGui::Separator();

	if (ImGui::CollapsingHeader("Edge Detection"))
	{
		ImGui::NewLine();
		ImGui::Separator();
		if (ImGui::CollapsingHeader("Sobel"))
		{
			ImGui::Selectable("X", &m_Edit->sobelX);
			ImGui::Selectable("Y", &m_Edit->sobelY);
			ImGui::Separator();
			if (ImGui::Button("Initialize Sobel")) m_Edit->Sobel();
		}

		ImGui::NewLine();
		ImGui::Separator();
	}
	ImGui::NewLine();
	ImGui::Separator();

	if (ImGui::Button("Apply Changes")) m_Edit->ApplyChanges();

}