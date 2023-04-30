#pragma once
#include "MSE.h"
class FastSearchSimilarImages :
    public MSE
{
    cv::Size targetSize_{ 32, 32 };
protected:
    cv::Mat originalMasterImage_{};
    ~FastSearchSimilarImages();
public:
    FastSearchSimilarImages();
    void Delete() override;
    void setMasterImage(const cv::Mat& master) override;
    
    double estimate(const cv::Mat& test) override;
    unsigned int predict(const cv::Mat& test) override;
};

