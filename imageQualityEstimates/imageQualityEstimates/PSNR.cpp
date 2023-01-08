#include "PSNR.h"

PSNR::~PSNR()
{
}

PSNR::PSNR()
{
}

void PSNR::Delete()
{
	delete this;
}

float PSNR::estimate(const cv::Mat& test)
{
	float mse{ MSE::estimate(test) };
	if (mse == 0.0)
		mse = 0.00000001;
	double toLog{ pow(255.0, 2.0) / mse };
	return 10.0 * log10(toLog);
}
