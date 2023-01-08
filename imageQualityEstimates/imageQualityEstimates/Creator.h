#pragma once
#include "MSE.h"
#include "PSNR.h"
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