#pragma once

#include "LarkinLab.h"

#include <opencv2/opencv.hpp>

class OpenCVImage
{
public:
	OpenCVImage(std::string& path);
	OpenCVImage();

	~OpenCVImage();

	void LoadMat(cv::Mat& frame);
	void UpdateMat(cv::Mat& frame);

	void SaveImage();
	void SaveImage(std::string& name);

	inline LarkinLab::OpenGLTexture* GetTexture() { return m_Texture; }

	// --- OpenCV Functionality --- //
	void GaussianBlur(int val);
	void FindCircles();
	void HoughCircles();
	cv::Mat& FindCountours(cv::Mat mat);


private:
	LarkinLab::OpenGLTexture* m_Texture;
	cv::Mat m_Mat;
};

