#pragma once
#include <iostream>
#include <vector>
#include <filesystem>
#include <random>
#include <algorithm>

namespace fs = std::filesystem;

class DataSetForQualityEstimate
{
public:
	DataSetForQualityEstimate();
	void setFileNameWithImages(const std::string& fileName);
	void setImagePaths();
	void next(std::vector<std::string>& output, unsigned int& label);
	void updateDataSet();
	size_t getQuantityPair() const;
private:

	fs::path fileWithImages_{};
	std::vector<std::string> classNames_;
	std::vector<std::vector<std::string>> imagePaths_;
	std::vector<int> numberActivImageInClass_;
	bool isEvenPair_{ true };
	unsigned int quantityClassesWithPairImage_{};
	unsigned int quantityNotNullClasses_{};
	size_t quantityPair_{};
	std::random_device rd{};
	std::mt19937 generator_{ rd() };

	size_t getRandomClassExept(size_t const classNumber) const;
	size_t getRandomClass() const;

	size_t getNotNullRandomClassExept(size_t const classNumber) const;
	size_t getNotNullRandomClass() const;

	size_t getNextClassWithNotUsedImages(unsigned int const quantityNotUsedImage, size_t const startClassNumber);

	bool thereDiferentPair();
	bool thereIdenticalPair();

	void getIdenticalPairImages(std::vector<std::string>& output);
	void getDiferentPairImages(std::vector<std::string>& output);
};

