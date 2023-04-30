#pragma once
#include "IImageQualityEstimates.h"
class MinkovskisNorm :
    public IImageQualityEstimate
{
protected:
    cv::Mat masterImage_{};
    ~MinkovskisNorm();
public:
    MinkovskisNorm();
    void Delete();
    
    double estimate(const cv::Mat& testImage) override;
    void setMasterImage(const cv::Mat& master) override;
    unsigned int predict(const cv::Mat& test) override;
};

