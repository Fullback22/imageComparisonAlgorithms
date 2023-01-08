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
    float estimate(const cv::Mat& test);
};

