#pragma once
#include "MSE.h"
class PSNR :
    public MSE
{
protected:
    ~PSNR();
public:
    PSNR();
    void Delete();
    double estimate(const cv::Mat& test);
    unsigned int predict(const cv::Mat& test) override;
};

