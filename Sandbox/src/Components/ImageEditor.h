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

	bool showEdit = false;
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
	int m_GaussBlurOld = 0;
	int m_GaussBlur = 0, m_Entre = 8, m_Threshold = 90, m_ThreshCenter = 100, m_CannyThresh = 100;

};

