#include "DataSetForQualityEstimate.h"

DataSetForQualityEstimate::DataSetForQualityEstimate()
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
	}
	return;
}