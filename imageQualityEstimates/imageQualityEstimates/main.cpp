// imageQualityEstimates.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include "Creator.h"

#include "Params.h"
#include "DataSetForQualityEstimate.h"

int main()
{
    Params parm;
    CreatorMse creatorMse{};
    CreatorPsnr creatorPsnr{};
    CreatorMinkovkisNorm creatorMn{};
    CreatorSsim creatorSsim{};
    CreatorFssi creatorFssi{};
    CreatorMediumHash creatorMediumHash{};
    Creator_pHash creator_pHash{};
    std::vector<Creator*> creators{ &creatorMse, &creatorPsnr, &creatorMn, &creatorSsim, &creatorFssi, &creatorMediumHash, &creator_pHash };
    std::list<IImageQualityEstimate*> estimates;

    for (const auto creator:creators)
    {
        estimates.push_back(creator->estiamteCreate());
    }

    DataSetForQualityEstimate ds{};
    ds.setFileNameWithImages(parm.directoryWithImages);
    ds.setImagePaths();
    ds.updateDataSet();

    size_t quantityIdenticalPairs{};
    size_t quantityDiferentPairs{};
    std::vector<unsigned int> quatityTrueIdenticalPairs(estimates.size(), 0);
    std::vector<unsigned int> quatityPredictIdenticalPairs(estimates.size(), 0);
    std::vector<unsigned int> quatityTrueDiferentlPairs(estimates.size(), 0);
    std::vector<unsigned int> quatityPredictDiferentPairs(estimates.size(), 0);
    std::vector<std::string> qualityEstimateNames{ "MSE","PSNR","L2","SSIM","Fast","mediumHash","pHash" };

    for (size_t i{}; i < ds.getQuantityPair(); ++i)
    {
        std::vector<std::string> imagesPath(2, "");
        unsigned int label;
        ds.next(imagesPath, label);
        try {
            cv::Mat buferForLoadImage{ cv::imread(imagesPath[0], cv::IMREAD_GRAYSCALE) };
            if (buferForLoadImage.empty())
                throw std::string{ "Main image is null" };

            cv::Size targetSize{ buferForLoadImage.size() };
            for (const auto estiamte : estimates)
                estiamte->setMasterImage(buferForLoadImage);
            
            buferForLoadImage = cv::imread(imagesPath[1], cv::IMREAD_GRAYSCALE);
            if (buferForLoadImage.empty())
                throw std::string{ "Test image is null" };

            cv::resize(buferForLoadImage, buferForLoadImage, targetSize);
            size_t estimateNumber{};
            for (const auto estiamte : estimates)
            {
                double curentEstimate{ estiamte->estimate(buferForLoadImage) };
                unsigned int predict{ estiamte->predict(buferForLoadImage) };
                if (predict == 1)
                    ++quatityPredictIdenticalPairs[estimateNumber];
                else
                    ++quatityPredictDiferentPairs[estimateNumber];

                if (predict == 1 && label == 1)
                    ++quatityTrueIdenticalPairs[estimateNumber];
                else if (predict == 0 && label == 0)
                    ++quatityTrueDiferentlPairs[estimateNumber];
                ++estimateNumber;
            }
            if (label == 1)
                ++quantityIdenticalPairs;
            else
                ++quantityDiferentPairs;
        }
        catch (const std::string& error)
        {
            std::cout << error << std::endl;
        }
    }
    for (const auto estiamte : estimates)
    {
        estiamte->Delete();
    }
    estimates.clear();

    std::ofstream outEstimate{ parm.fileNameForSave, std::ofstream::out | std::ofstream::trunc };
    size_t estimateNumber{};
    for (size_t i{};i< qualityEstimateNames.size();++i)
    {
        outEstimate << qualityEstimateNames[i] << std::endl;
        double pIdentical{ static_cast<double>(quatityTrueIdenticalPairs[i]) / quatityPredictIdenticalPairs[i] };
        double rIdentical{ static_cast<double>(quatityTrueIdenticalPairs[i]) / quantityIdenticalPairs };
        double pDiferent{ static_cast<double>(quatityTrueDiferentlPairs[i]) / quatityPredictDiferentPairs[i] };
        double rDiferent{ static_cast<double>(quatityTrueDiferentlPairs[i]) / quantityDiferentPairs };
        outEstimate << "Precision Identical:\t" << pIdentical << std::endl;
        outEstimate << "Recall Identical:\t" << rIdentical << std::endl;
        outEstimate << "Precision Diferent:\t" << pDiferent << std::endl;
        outEstimate << "Recall Diferent:\t" << rDiferent << std::endl;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
