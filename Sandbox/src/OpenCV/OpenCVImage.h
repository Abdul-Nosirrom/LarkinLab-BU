#pragma once

#include "LarkinLab.h"

#include <opencv2/imgcodecs.hpp>

class OpenCVImage
{
public:
	OpenCVImage(std::string& path);

private:
	LarkinLab::OpenGLTexture* m_Texture;
	cv::Mat m_Image;
};

