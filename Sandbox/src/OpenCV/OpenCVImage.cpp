#include "OpenCVImage.h"

using namespace LarkinLab;

OpenCVImage::OpenCVImage(std::string& path)
{
	m_Texture = new OpenGLTexture(path);
	m_Image = cv::imread(path);
}

OpenCVImage::~OpenCVImage()
{
	delete(m_Texture);
}