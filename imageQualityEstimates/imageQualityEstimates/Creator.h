#pragma once
#include "MSE.h"
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