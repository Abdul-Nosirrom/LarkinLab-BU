#include "OpenCVImage.h"

using namespace LarkinLab;

OpenCVImage::OpenCVImage(std::string& path)
{
	m_Texture = new OpenGLTexture(path);
	cv::Mat m_Image = cv::imread(path);
}