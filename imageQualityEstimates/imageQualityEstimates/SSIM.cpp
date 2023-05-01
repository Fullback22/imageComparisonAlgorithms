#include "SSIM.h"

SSIM::~SSIM()
{
}

SSIM::SSIM()
{
}

void SSIM::Delete()
{
	delete this;
}

void SSIM::setMasterImage(const cv::Mat& master)
{
	master.copyTo(masterImage_);
	mediumMaster_ = medium(master);
	varianceMaster_ = variance(master, mediumMaster_);
}

unsigned int SSIM::predict(const cv::Mat& test)
{
	if (estimate(test) > 0.5)
		return 1;
	else
		return 0;
}

double SSIM::estimate(const cv::Mat& test)
{
	if (test.size() == masterImage_.size())
	{
		double mediumTest{ medium(test) };
		double varianceTest{ variance(test, mediumTest) };
		double covariance_{ covariance(masterImage_, test, mediumMaster_, mediumTest) };
		
		double numerator{ (2.0 * mediumMaster_ * mediumTest + C1_) * (2 * covariance_ + C2_) };
		double denominator{ (pow(mediumMaster_, 2 ) + pow(mediumTest, 2) + C1_) * (varianceMaster_ + varianceTest + C2_) };
		return numerator / denominator;
	}
	else
	{
		throw "The images have different size";
	}
}
