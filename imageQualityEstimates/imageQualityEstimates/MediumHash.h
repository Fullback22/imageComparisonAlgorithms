#pragma once
#include "IImageQualityEstimates.h"
#include "mathFunctionForMat.h"
class MediumHash :
    public IImageQualityEstimate
{
protected:
    cv::Size targetImageSize_{ 8,8 };
    size_t hashSize_{ 64 };
    char* hashMasterImage_{ nullptr };
    
    cv::Mat prepareImageForComputeHash(const cv::Mat& image) const;
    void createBinaryImage(cv::Mat& image, int const threshold) const;
    void computeMediumHash(const cv::Mat& originalImage, char*& hash) const;
    ~MediumHash();
public:
    MediumHash();
    void Delete();
    void setMasterImage(const cv::Mat& master) override;
    double estimate(const cv::Mat& test) override;
};

