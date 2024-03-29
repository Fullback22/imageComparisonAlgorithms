#pragma once
#include "IImageQualityEstimates.h"
class MSE :
    public IImageQualityEstimate
{
protected:
    cv::Mat masterImage_{};
    ~MSE();
public:
    MSE();
    void Delete() override;
        
    void setMasterImage(const cv::Mat& master) override;
    unsigned int predict(const cv::Mat& test) override;
    double estimate(const cv::Mat& test) override;
};
