#pragma once
#include "IImageQualityEstimates.h"
class MSE :
    public IImageQualityEstimate
{
    cv::Mat masterImage_{};

   
protected:
    ~MSE();
public:
    MSE();
    void Delete() override;
        
    void setMasterImage(const cv::Mat& master) override;
    
    float estimate(const cv::Mat& test) override;
};
