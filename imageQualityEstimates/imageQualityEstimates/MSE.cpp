#include "MSE.h"

MSE::MSE()
{
}

MSE::~MSE()
{
}

void MSE::Delete()
{
	delete this;
}

void MSE::setMasterImage(const cv::Mat& master)
{
	master.copyTo(masterImage_);
}

unsigned int MSE::predict(const cv::Mat& test)
{
	if (estimate(test) < 9753.75)
		return 1;
	else
		return 0;
}

double MSE::estimate(const cv::Mat& test)
{
	if (test.size() == masterImage_.size())
	{
		double sum{};
		for (size_t i{}; i < masterImage_.size().height; ++i)
		{
			for (size_t j{}; j < masterImage_.size().width; ++j)
			{
				int delta{ masterImage_.at<uchar>(i, j) - test.at<uchar>(i,j) };
				sum += pow(delta, 2.0);
			}
		}
		return sum / (masterImage_.size().area());
	}
	else
	{
		throw std::string{ "The images have different size" };
	}
}
