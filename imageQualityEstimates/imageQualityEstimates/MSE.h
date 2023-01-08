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
    
    float estimate(const cv::Mat& test) override;
};
