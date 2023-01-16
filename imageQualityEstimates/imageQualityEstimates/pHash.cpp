#include "pHash.h"

cv::Mat pHash::prepareImageForComputeHash(const cv::Mat& image) const
{
	cv::Mat dctImage{};
	cv::resize(image, dctImage, dctImageSize_);
	dctImage.convertTo(dctImage, CV_32F);

	for (size_t i{}; i < dctImage.size().width; ++i)
	{
		for (size_t j{}; j < dctImage.size().height; ++j)
			dctImage.at<float>(i, j) /= 255.0;
	}

	cv::dct(dctImage, dctImage);

	cv::Rect dctRoi{ cv::Point{0,0}, targetImageSize_ };

	cv::Mat targetImage{  };
	dctImage(dctRoi).copyTo(targetImage);
	double mediumBrigthness{ 0 };

	for (size_t i{}; i < dctImage.size().width; ++i)
	{
		for (size_t j{}; j < dctImage.size().height; ++j)
			mediumBrigthness += dctImage.at<float>(i, j);
	}

	mediumBrigthness -= dctImage.at<float>(0, 0);
	mediumBrigthness /= (hashSize_ - 1);

	createBinaryImage(targetImage, mediumBrigthness);
	return targetImage;
}

void pHash::createBinaryImage(cv::Mat& image, int const threshold) const
{
	for (size_t i{}; i < image.size().width; ++i)
	{
		for (size_t j{}; j < image.size().height; ++j)
		{
			if (image.at<float>(i, j) >= threshold)
				image.at<float>(i, j) = 1.0;
			else
				image.at<float>(i, j) = 0.0;
		}
	}
}

void pHash::compute_pHash(const cv::Mat& originalImage, char*& hash) const
{
	cv::Mat binaryImage{ prepareImageForComputeHash(originalImage) };
	if (hash != nullptr)
		delete[]hash;
	hash = new char[hashSize_];
	for (size_t i{}; i < binaryImage.size().width; ++i)
	{
		for (size_t j{}; j < binaryImage.size().height; ++j)
		{
			size_t index{ i * binaryImage.size().width + j };
			if (binaryImage.at<float>(i, j) == 1.0)
				hash[index] = 1;
			else
				hash[index] = 0;
		}
	}
}

pHash::~pHash()
{
	delete[] hashMasterImage_;
	hashMasterImage_ = nullptr;
}

pHash::pHash()
{
}

void pHash::Delete()
{
	delete this;
}

void pHash::setMasterImage(const cv::Mat& master)
{
	compute_pHash(master, hashMasterImage_);
}

double pHash::estimate(const cv::Mat& test)
{
	char* hashTestImage{ nullptr };
	compute_pHash(test, hashTestImage);
	int hammingDistance{ 0 };
	for (size_t i{}; i < hashSize_; ++i)
	{
		hammingDistance += abs(hashTestImage[i] - hashMasterImage_[i]);
	}
	delete[]hashTestImage;
	hashTestImage = nullptr;
	return static_cast<double>(hammingDistance);
}
