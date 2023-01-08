#include "Creator.h"

IImageQualityEstimate* CreatorMse::estiamteCreate()
{
	return static_cast<IImageQualityEstimate*>(new MSE());
}

IImageQualityEstimate* CreatorPsnr::estiamteCreate()
{
	return static_cast<IImageQualityEstimate*>(new PSNR());
}
