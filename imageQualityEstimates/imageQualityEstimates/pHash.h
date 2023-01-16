#pragma once
#include "IImageQualityEstimates.h"
#include "mathFunctionForMat.h"

class pHash :
    public IImageQualityEstimate
{
protected:
    cv::Size dctImageSize_{ 32,32 };
    cv::Size targetImageSize_{ 8,8 };
    size_t hashSize_{ 64 };
    char* hashMasterImage_{ nullptr };

    cv::Mat prepareImageForComputeHash(const cv::Mat& image) const;
    void createBinaryImage(cv::Mat& image, int const threshold) const;
    void compute_pHash(const cv::Mat& originalImage, char*& hash) const;
    ~pHash();
public:
    pHash();
    void Delete();
    void setMasterImage(const cv::Mat& master) override;
    double estimate(const cv::Mat& test) override;
};

