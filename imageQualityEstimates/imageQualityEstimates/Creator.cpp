#include "Creator.h"

IImageQualityEstimate* CreatorMse::estiamteCreate()
{
	return static_cast<IImageQualityEstimate*>(new MSE());
}
