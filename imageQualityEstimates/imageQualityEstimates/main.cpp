// imageQualityEstimates.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <list>
#include "Creator.h"

#include "Params.h"
#include "DataSetForQualityEstimate.h"

int main()
{
    DataSetForQualityEstimate ds{};
    ds.setFileNameWithImages("E:\\work\\test");
    ds.setImagePaths();

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
    try {
        cv::Mat buferForLoadImage{};
        for (const auto estiamte : estimates)
        {
            buferForLoadImage = cv::imread(parm.masterImageName, cv::IMREAD_GRAYSCALE);
            if (!buferForLoadImage.empty())
                estiamte->setMasterImage(buferForLoadImage);
            else
            {
                throw std::string{ "Main image is null" };
            }
        }

        for (const auto estiamte : estimates)
        {
            buferForLoadImage = cv::imread(parm.testImageName, cv::IMREAD_GRAYSCALE);
            if (!buferForLoadImage.empty())
            {
                double curentEstimate{ estiamte->estimate(buferForLoadImage) };
                std::cout << curentEstimate << std::endl;
            }
            else
            {
                throw std::string{ "Test image is null" };
            }
        }
    }
    catch (const std::string& error)
    {
        std::cout << error << std::endl;
    }

    for (const auto estiamte : estimates)
    {
        estiamte->Delete();
    }
    estimates.clear();
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
