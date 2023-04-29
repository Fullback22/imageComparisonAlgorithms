#pragma once
#include <iostream>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

class DataSetForQualityEstimate
{
public:
	DataSetForQualityEstimate();
	void setFileNameWithImages(const std::string& fileName);
	void setImagePaths();
private:

	fs::path fileWithImages_{};
	std::vector<std::string> classNames_;
	std::vector<std::vector<std::string>> imagePaths_;
};

