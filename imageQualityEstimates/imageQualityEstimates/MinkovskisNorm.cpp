#include "MinkovskisNorm.h"

MinkovskisNorm::~MinkovskisNorm()
{
}

MinkovskisNorm::MinkovskisNorm()
{
}

void MinkovskisNorm::Delete()
{
	delete this;
}

double MinkovskisNorm::estimate(const cv::Mat& test)
{
	
	if (test.size() == masterImage_.size())
	{
		double const P{ 2.0 };
		double sum{};
		for (size_t i{}; i < masterImage_.size().height; ++i)
		{
			for (size_t j{}; j < masterImage_.size().width; ++j)
			{
				int delta{ masterImage_.at<uchar>(i, j) - test.at<uchar>(i,j) };
				sum += pow(delta, P);
			}
		}
		
		return pow(sum, 1.0 / P);
	}
	else
	{
		throw "The images have different size";
	}
}

void MinkovskisNorm::setMasterImage(const cv::Mat& master)
{
	master.copyTo(masterImage_);
}

unsigned int MinkovskisNorm::predict(const cv::Mat& test)
{
	if (estimate(test) < 41400)
		return 1;
	else
		return 0;
}
