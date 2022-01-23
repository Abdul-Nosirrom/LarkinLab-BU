#pragma once

#include <LarkinLab.h>

#include "OpenCV/OpenCVImage.h"

class ImageEditor
{
public:
	ImageEditor();

	void OnImGuiRender();

	void LoadImageToEditor(std::string path);
	void ShowImage(const char* window, OpenCVImage * image);
	void Save();
	void SaveAs(std::string path);

	bool showEdit = true;
	bool showOriginal = true;

private:
	void ShowParameters();
	void ApplyEdits();

	std::vector<OpenCVImage> m_Data;

	OpenCVImage* m_Image = NULL;
	OpenCVImage* m_Edit = NULL;
	std::string m_ImagePath;
	bool m_ImageLoaded = false;

	// OpenCV Parameters
	int m_GaussBlurOld = 1;
	int m_GaussBlur = 1, m_Entre = 8, m_Threshold = 90, m_ThreshCenter = 100, m_CannyThresh = 100;

	bool m_findCircles = false;
	bool m_applyBlur = false;
	bool m_findContours = false;
};

