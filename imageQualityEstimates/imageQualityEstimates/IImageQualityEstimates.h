#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

class IImageQualityEstimate
{
protected:
	~IImageQualityEstimate() = default;

public:
	IImageQualityEstimate& operator= (const IImageQualityEstimate&) = delete;
	virtual void Delete() = 0;

	virtual unsigned int predict(const cv::Mat& test) = 0;
	virtual double estimate(const cv::Mat& test) = 0;
	virtual void setMasterImage(const cv::Mat& master) = 0;
};

