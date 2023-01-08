#pragma once
#include "IImageQualityEstimates.h"
#include "mathFunctionForMat.h"

class SSIM :
    public IImageQualityEstimate
{ 
    int const L_{ 255 };
    double const K1_{ 0.01 };
    double const K2_{ 0.03 };

    double C1_{ pow(K1_ * L_, 2.0) };
    double C2_{ pow(K2_ * L_, 2.0) };
    
    double mediumMaster_{};
    double varianceMaster_{};

protected:
    cv::Mat masterImage_{};
    ~SSIM();
public:
    SSIM();
    void Delete() override;
    void setMasterImage(const cv::Mat& master) override;

    double estimate(const cv::Mat& test) override;
};

