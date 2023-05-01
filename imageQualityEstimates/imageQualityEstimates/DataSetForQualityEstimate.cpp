#include "DataSetForQualityEstimate.h"

DataSetForQualityEstimate::DataSetForQualityEstimate() :
	classNames_(0),
	imagePaths_(0),
	numberActivImageInClass_(0)
{
}

void DataSetForQualityEstimate::setFileNameWithImages(const std::string& fileName)
{
	fileWithImages_ = fileName;
}
void DataSetForQualityEstimate::setImagePaths()
{
	size_t quantitClasses{};
	for (const auto& directory : fs::directory_iterator{ fileWithImages_ })
	{
		if (fs::is_directory(directory.path()))
			++quantitClasses;
	}

	imagePaths_.resize(quantitClasses);
	classNames_.resize(quantitClasses);

	size_t classNumber{};
	size_t sumQuantitImages{};
	for (const auto& directory : fs::directory_iterator{ fileWithImages_ })
	{
		size_t quantitImages{};
		for (const auto& image : fs::directory_iterator{ directory })
		{
			if (!fs::is_directory(image.path()))
				++quantitImages;
		}
		imagePaths_[classNumber].resize(quantitImages);
		classNames_[classNumber] = directory.path().filename().string();

		size_t imageNumber{};
		for (const auto& image : fs::directory_iterator{ directory })
		{
			if (!fs::is_directory(image.path()))
			{
				imagePaths_[classNumber][imageNumber] = image.path().string();
				++imageNumber;
			}
		}
		++classNumber;
		sumQuantitImages += quantitImages;
	}
	quantityPair_ = sumQuantitImages / 2;
}

void DataSetForQualityEstimate::next(std::vector<std::string>& output, unsigned int& label)
{
	if (!thereDiferentPair() && !thereIdenticalPair())
	{
		output.resize(0);
	}
	else
	{
		output.resize(2);

		if ( (isEvenPair_ && thereIdenticalPair()) || (!isEvenPair_ && !thereDiferentPair()))
		{
			getIdenticalPairImages(output);
			label = 1;
		}
		else
		{
			getDiferentPairImages(output);
			label = 0;
		}
		isEvenPair_ = !isEvenPair_;
	}
}

void DataSetForQualityEstimate::updateDataSet()
{
	numberActivImageInClass_.resize(imagePaths_.size());
	for (size_t i{}; i < numberActivImageInClass_.size(); ++i)
	{
		numberActivImageInClass_[i] = imagePaths_[i].size() - 1;
		if (numberActivImageInClass_[i] > 1)
		{
			++quantityClassesWithPairImage_;
			++quantityNotNullClasses_;
		}
		else if (numberActivImageInClass_[i] > 1)
			++quantityNotNullClasses_;
		std::shuffle(imagePaths_[i].begin(), imagePaths_[i].end(), generator_);
	}
	isEvenPair_ = true;
}

size_t DataSetForQualityEstimate::getQuantityPair() const
{
	return quantityPair_;
}

size_t DataSetForQualityEstimate::getRandomClassExept(size_t const classNumber) const
{
	std::random_device rd1{};
	std::mt19937 gen{ rd1() };
	std::vector<int> distribution(classNames_.size(), classNames_.size());
	distribution[classNumber] = 0;
	std::discrete_distribution<> classDistribution(distribution.begin(), distribution.end());
	return classDistribution(gen);
}

size_t DataSetForQualityEstimate::getRandomClass() const
{
	std::random_device rd1{};
	std::mt19937 gen{ rd1() };
	std::uniform_int_distribution<> classDistribution(1,6);
	return classDistribution(gen);
}

size_t DataSetForQualityEstimate::getNotNullRandomClassExept(size_t const classNumber) const
{
	std::random_device rd1{};
	std::mt19937 gen{ rd1() };
	std::vector<int> distribution(classNames_.size(), classNames_.size());
	distribution[classNumber] = 0;
	for (size_t i{}; i < distribution.size(); ++i)
	{
		if(numberActivImageInClass_[i] < 0)
			distribution[i] = 0;
	}
	std::discrete_distribution<> classDistribution(distribution.begin(), distribution.end());
	return classDistribution(gen);
}

size_t DataSetForQualityEstimate::getNotNullRandomClass() const
{
	std::random_device rd1{};
	std::mt19937 gen{ rd1() };
	std::vector<int> distribution(classNames_.size(), classNames_.size());
	for (size_t i{}; i < distribution.size(); ++i)
	{
		if (numberActivImageInClass_[i] < 0)
			distribution[i] = 0;
	}
	std::discrete_distribution<> classDistribution(distribution.begin(), distribution.end());
	return classDistribution(gen);
}

size_t DataSetForQualityEstimate::getNextClassWithNotUsedImages(unsigned int const quantityNotUsedImage, size_t const startClassNumber)
{
	for (size_t i{ startClassNumber + 1 }; i < imagePaths_.size(); ++i)
	{
		if (numberActivImageInClass_[i] >= quantityNotUsedImage - 1)
			return i;
	}
	for (size_t i{ 0 }; i < startClassNumber; ++i)
	{
		if (numberActivImageInClass_[i] >= quantityNotUsedImage - 1)
			return i;
	}
	return -1;
}

bool DataSetForQualityEstimate::thereDiferentPair()
{
	if (quantityNotNullClasses_ > 1)
		return true;
	else
		return false;
}

bool DataSetForQualityEstimate::thereIdenticalPair()
{
	if (quantityClassesWithPairImage_ > 0)
		return true;
	else
		return false;
}

void DataSetForQualityEstimate::getIdenticalPairImages(std::vector<std::string>& output)
{
	size_t classImage{ getNotNullRandomClass() };
	if (numberActivImageInClass_[classImage] < 1)
		classImage = getNextClassWithNotUsedImages(2, classImage);
	output[0] = imagePaths_[classImage][numberActivImageInClass_[classImage]];
	--numberActivImageInClass_[classImage];

	output[1] = imagePaths_[classImage][numberActivImageInClass_[classImage]];
	--numberActivImageInClass_[classImage];
	if (numberActivImageInClass_[classImage] == -1)
	{
		--quantityClassesWithPairImage_;
		--quantityNotNullClasses_;
	}
	else if (numberActivImageInClass_[classImage] == 0)
		--quantityClassesWithPairImage_;
}

void DataSetForQualityEstimate::getDiferentPairImages(std::vector<std::string>& output)
{
	size_t firstClassImage{ getNotNullRandomClass() };
	output[0] = imagePaths_[firstClassImage][numberActivImageInClass_[firstClassImage]];
	--numberActivImageInClass_[firstClassImage];
	
	size_t secondClassImage{ getNotNullRandomClassExept(firstClassImage) };
	output[1] = imagePaths_[secondClassImage][numberActivImageInClass_[secondClassImage]];
	--numberActivImageInClass_[secondClassImage];

	if (numberActivImageInClass_[firstClassImage] == -1)
		--quantityNotNullClasses_;
	else if (numberActivImageInClass_[firstClassImage] == 0)
		--quantityClassesWithPairImage_;

	if (numberActivImageInClass_[secondClassImage] == -1)
		--quantityNotNullClasses_;
	else if (numberActivImageInClass_[secondClassImage] == 0)
		--quantityClassesWithPairImage_;
}
