#include "OpenCVImage.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

// Need to figure out where the enums i listed as defines are

#define CV_BGR2RGB 4	// Weird color swap with CV Mats, cant find where this is defined rn
#define CV_RGB2GRAY 7
#define CV_HOUGH_GRADIENT 3

int Round(double x);
static cv::Mat m_Draw;

using namespace LarkinLab;

OpenCVImage::OpenCVImage() {}

OpenCVImage::OpenCVImage(std::string& path)
{
	m_Mat = cv::imread(path, cv::ImreadModes::IMREAD_ANYCOLOR);
	cv::cvtColor(m_Mat, m_Mat, cv::COLOR_BGR2RGB); // OpenCV seems to load with BGR for some reason
	m_Texture = new OpenGLTexture(m_Mat.ptr(), m_Mat.cols, m_Mat.rows);
	m_baseMat = m_Mat.clone();
	m_Path = path;
}

OpenCVImage::~OpenCVImage()
{
	delete(m_Texture);
}

void OpenCVImage::SaveImage(std::string& path)
{
	cv::cvtColor(m_baseMat, m_baseMat, cv::COLOR_RGB2BGR);
	cv::imwrite(path, m_baseMat);
	cv::cvtColor(m_baseMat, m_baseMat, cv::COLOR_BGR2RGB);
}

void OpenCVImage::LoadMat(cv::Mat& frame)
{
	m_Texture->LoadTexture(frame.ptr(), frame.cols, frame.rows);
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
	else
	{	
		LL_TRACE("Channels {0}", frame.channels());
		m_Texture->UpdateTexture(frame.ptr(), frame.channels());
		//m_Texture->LoadTexture(frame.ptr(), frame.cols, frame.rows, frame.channels());
	}
	// Do we need to bind the texture to something such that we can update a seperate copy?
}

void OpenCVImage::ApplyChanges()
{
	m_Mat = m_Draw.clone();
	m_baseMat = m_Draw.clone();
}

////////////////////////////////////////////////////////////////////
void OpenCVImage::Grayscale()
{
	if (m_Mat.empty())
	{
		LL_ERROR("Frame is empty");
		return;
	}
	m_Draw.release();
	cv::cvtColor(m_baseMat, m_Draw, cv::COLOR_RGB2GRAY);
	UpdateMat(m_Draw);
}

void OpenCVImage::GaussianBlur(int val)
{
	cv::GaussianBlur(m_Mat, m_baseMat, cv::Size(val, val), 0, 0);
	UpdateMat(m_baseMat);
}

void OpenCVImage::FindCircles(int entre, int threshold, int threshold_center)
{
	
	cv::Mat src_gray;
	if (m_baseMat.type() == CV_8UC3)
		cv::cvtColor(m_baseMat, src_gray, CV_RGB2GRAY);
	
	std::vector<cv::Vec3f> circles;

	if (entre == 0) entre += 1;
	
	// HUGH CIRCLES CAUSES CRASH FOR SOME REASON, AVOID
	cv::HoughCircles(src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows / entre, threshold, threshold_center, 0, 0);
	
	
	for (size_t i = 0; i < circles.size(); i++)
	{
		cv::Point center(Round(circles[i][0]), Round(circles[i][1]));
		int radius = Round(circles[i][2]);
		// Circle center
		cv::circle(m_baseMat, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);
		cv::circle(m_baseMat, center, radius, cv::Scalar(0, 255, 0), 3, cv::LINE_AA, 0);
	}
	
	
	UpdateMat(m_baseMat);
	
}



void OpenCVImage::FindCountours(int thresh)
{
	cv::RNG rng = cv::RNG(12345);
	cv::Mat canny_output;
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	/// Detect edges using canny
	cv::Canny(m_baseMat, canny_output, thresh, thresh * 4, 3);

	// Find contours needs an image of one channel so we need to catch it ..TODO
	cv::findContours(canny_output, contours, hierarchy, 0, 1, cv::Point(0, 0));
	
	/// Draw contours
	m_Draw.release();
	m_Draw = cv::Mat::zeros(canny_output.size(), CV_8UC3);

	for (int i = 0; i < contours.size(); i++)
	{
		cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		cv::drawContours(m_Draw, contours, i, color, 1, cv::LINE_AA, hierarchy, 0, cv::Point(0, 0));
	}


	UpdateMat(m_Draw);
}

void OpenCVImage::FindBlobs()
{
	/// Draw contours
	m_Draw.release();
	m_Draw = cv::Mat::zeros(m_baseMat.size(), CV_8UC3);

	std::vector<cv::KeyPoint> keypoints;
	cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(blobDetectionParams);

	detector->detect(m_baseMat, keypoints);
	cv::drawKeypoints(m_baseMat, keypoints, m_Draw, cv::Scalar(255, 0, 0), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	UpdateMat(m_Draw); 
}

void OpenCVImage::Sobel()
{
	m_Draw.release();
	m_Draw = cv::Mat::zeros(m_baseMat.size(), CV_8UC3);
	cv::Sobel(m_baseMat, m_Draw, CV_64F, sobelX ? 1 : 0, sobelY ? 1 : 0, 3);
	UpdateMat(m_Draw);
}

// Dirty helper until i figure out whats missing in my opencv includes
int Round(double x) {
	int y;
	if (x >= (int)x + 0.5)
		y = (int)x++;
	else
		y = (int)x;
	return y;
}