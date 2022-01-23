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
	void ApplyChanges();

	void SaveImage(std::string& name);

	inline LarkinLab::OpenGLTexture* GetTexture() { return m_Texture; }

	// --- OpenCV Functionality --- //

	// --- Color Modifiers --- //
	void Grayscale();

	void GaussianBlur(int val);
	void FindCircles(int entre, int threshold, int threshold_center);
	void FindCountours(int thresh);
	void FindBlobs();
	void Sobel();



	// Blob Detection Parameters //
	cv::SimpleBlobDetector::Params blobDetectionParams;
	bool sobelX, sobelY;

private:
	LarkinLab::OpenGLTexture* m_Texture;
	std::string m_Path;
	cv::Mat m_Mat;
	cv::Mat m_baseMat;

};

