#pragma once
#include "MSE.h"
#include "PSNR.h"
#include "MinkovskisNorm.h"
#include "SSIM.h"
class Creator
{
public:
	virtual IImageQualityEstimate* estiamteCreate() = 0;
};

class CreatorMse : public Creator
{
public:
	IImageQualityEstimate* estiamteCreate() override;
};

class CreatorPsnr : public Creator
{
public:
	IImageQualityEstimate* estiamteCreate() override;
};

class CreatorMinkovkisNorm : public Creator
{
public:
	IImageQualityEstimate* estiamteCreate() override;
};

class CreatorSsim : public Creator
{
public:
	IImageQualityEstimate* estiamteCreate() override;
};