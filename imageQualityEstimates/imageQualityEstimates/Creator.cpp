#include "Creator.h"

IImageQualityEstimate* CreatorMse::estiamteCreate()
{
	return static_cast<IImageQualityEstimate*>(new MSE());
}

IImageQualityEstimate* CreatorPsnr::estiamteCreate()
{
	return static_cast<IImageQualityEstimate*>(new PSNR());
}

IImageQualityEstimate* CreatorMinkovkisNorm::estiamteCreate()
{
	return static_cast<IImageQualityEstimate*>(new MinkovskisNorm());
}

IImageQualityEstimate* CreatorSsim::estiamteCreate()
{
	return static_cast<IImageQualityEstimate*>(new SSIM());
}
