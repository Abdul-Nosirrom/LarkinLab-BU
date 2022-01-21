#include "OpenCVImage.h"

#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>


using namespace LarkinLab;

OpenCVImage::OpenCVImage() {}

OpenCVImage::OpenCVImage(std::string& path)
{
	m_Texture = new OpenGLTexture(path);
	m_Mat = cv::imread(path);
}

OpenCVImage::~OpenCVImage()
{
	delete(m_Texture);
}

void OpenCVImage::LoadMat(cv::Mat& frame)
{
	m_Texture->LoadTexture(frame.ptr());
	m_Mat = frame;
}

void OpenCVImage::UpdateMat(cv::Mat& frame)
{
	if (frame.size() != m_Mat.size())
	{
		m_Mat.release();
		m_Texture->DeleteTexture();
		LoadMat(frame);
	}

	LoadMat(frame);

	// Do we need to bind the texture to something such that we can update a seperate copy?
}

void OpenCVImage::GaussianBlur(int val)
{
	cv::Mat blurApplied = m_Mat.clone();
	cv::GaussianBlur(m_Mat, blurApplied, cv::Size(val, val), 0, 0);
	UpdateMat(blurApplied);
}

void OpenCVImage::FindCircles()
{

}

void OpenCVImage::HoughCircles()
{

}

cv::Mat& OpenCVImage::FindCountours(cv::Mat mat)
{
	return mat;
}