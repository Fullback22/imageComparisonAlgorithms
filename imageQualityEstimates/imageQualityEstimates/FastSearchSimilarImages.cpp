#include "FastSearchSimilarImages.h"

FastSearchSimilarImages::~FastSearchSimilarImages()
{
}

FastSearchSimilarImages::FastSearchSimilarImages()
{
}

void FastSearchSimilarImages::Delete()
{
	delete this;
}

void FastSearchSimilarImages::setMasterImage(const cv::Mat& master)
{
	master.copyTo(originalMasterImage_);
	cv::resize(originalMasterImage_, masterImage_, targetSize_);
}

double FastSearchSimilarImages::estimate(const cv::Mat& test)
{
	cv::Mat resizeTestImage{};
	cv::resize(test, resizeTestImage, targetSize_);
	return MSE::estimate(resizeTestImage);
}
