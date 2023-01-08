#pragma once
#include "IImageQualityEstimates.h"
class SSIM :
    public IImageQualityEstimate
{ 
protected:
    cv::Mat masterImage_{};
    ~SSIM();
public:
    SSIM();
    void Delete() override;
    void setMasterImage(const cv::Mat& master) override;

    double estimate(const cv::Mat& test) override;
};

