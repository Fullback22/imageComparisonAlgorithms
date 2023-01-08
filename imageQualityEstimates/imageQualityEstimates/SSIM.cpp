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
}
