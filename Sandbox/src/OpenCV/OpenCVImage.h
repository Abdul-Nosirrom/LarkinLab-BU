#pragma once

#include "LarkinLab.h"

#include <opencv2/imgcodecs.hpp>

class OpenCVImage
{
public:
	OpenCVImage(std::string& path);

	~OpenCVImage();

	void SaveImage();
	void SaveImage(std::string& name);

	inline LarkinLab::OpenGLTexture* GetTexture() { return m_Texture; }

private:
	LarkinLab::OpenGLTexture* m_Texture;
	cv::Mat m_Image;
};

