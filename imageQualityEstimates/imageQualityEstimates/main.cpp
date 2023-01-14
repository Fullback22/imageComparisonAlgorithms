// imageQualityEstimates.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <list>
#include "Creator.h"

#include "Params.h"
int main()
{
    Params parm;
    CreatorMse creatorMse{};
    CreatorPsnr creatorPsnr{};
    CreatorMinkovkisNorm creatorMn{};
    CreatorSsim creatorSsim{};
    CreatorFssi creatorFssi{};
    std::vector<Creator*> creators{ &creatorMse, &creatorPsnr, &creatorMn, &creatorSsim, &creatorFssi };
    std::list<IImageQualityEstimate*> estimates;

    for (const auto creator:creators)
    {
        estimates.push_back(creator->estiamteCreate());
    }

    for (const auto estiamte : estimates)
    {
        estiamte->setMasterImage(cv::imread(parm.masterImageName, cv::IMREAD_GRAYSCALE));
    }

    for (const auto estiamte : estimates)
    {
        double curentEstimate{ estiamte->estimate(cv::imread(parm.testImageName, cv::IMREAD_GRAYSCALE)) };
        std::cout << curentEstimate << std::endl;
    }

    for (const auto estiamte : estimates)
    {
        estiamte->Delete();
    }
    estimates.clear();

    std::cout << "Hello World!\n";
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
