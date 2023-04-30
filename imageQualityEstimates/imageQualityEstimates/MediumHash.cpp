#include "MediumHash.h"

cv::Mat MediumHash::prepareImageForComputeHash(const cv::Mat& image) const
{
	cv::Mat resizeImage{};
	cv::resize(image, resizeImage, targetImageSize_);

	int mediumBrigthness{ static_cast<int>(medium(resizeImage)) };
	createBinaryImage(resizeImage, mediumBrigthness);
	return resizeImage;
}

void MediumHash::createBinaryImage(cv::Mat& image, int const threshold) const
{
	for (size_t i{}; i < image.size().height; ++i)
	{
		for (size_t j{}; j < image.size().width; ++j)
		{
			if (image.at<uchar>(i, j) >= threshold)
				image.at<uchar>(i, j) = 255;
			else
				image.at<uchar>(i, j) = 0;
		}
	}
}

void MediumHash::computeMediumHash(const cv::Mat& originalImage, char*& hash) const
{
	cv::Mat binaryImage{ prepareImageForComputeHash(originalImage) };
	if (hash != nullptr)
		delete[]hash;
	hash = new char[hashSize_];
	for (size_t i{}; i < binaryImage.size().height; ++i)
	{
		for (size_t j{}; j < binaryImage.size().width; ++j)
		{
			size_t index{ i * binaryImage.size().height + j };
			if (binaryImage.at<uchar>(i, j) == 255)
				hash[index] = 1;
			else
				hash[index] = 0;
		}
	}
}

MediumHash::~MediumHash()
{
	delete []hashMasterImage_;
	hashMasterImage_ = nullptr;
}

MediumHash::MediumHash()
{
}

void MediumHash::Delete()
{
	delete this;
}

void MediumHash::setMasterImage(const cv::Mat& master)
{
	computeMediumHash(master, hashMasterImage_);
}

double MediumHash::estimate(const cv::Mat& test)
{
	char* hashTestImage{ nullptr };
	computeMediumHash(test, hashTestImage);
	int hammingDistance{ 0 };
	for (size_t i{}; i < hashSize_; ++i)
	{
		hammingDistance += abs(hashTestImage[i] - hashMasterImage_[i]);
	}
	delete[]hashTestImage;
	hashTestImage = nullptr;
	return static_cast<double>(hammingDistance);
}

unsigned int MediumHash::predict(const cv::Mat& test)
{
	if (estimate(test) < 10)
		return 1;
	else
		return 0;
}
