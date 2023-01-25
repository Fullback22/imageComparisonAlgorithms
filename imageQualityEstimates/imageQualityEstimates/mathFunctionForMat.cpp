#include "mathFunctionForMat.h"

double medium(const cv::Mat& image)
{
    int sum{};
    for (size_t i{}; i < image.size().height; ++i)
    {
        for (size_t j{}; j < image.size().width; ++j)
        {
            sum += image.at<uchar>(i, j);
        }
    }
    return static_cast<double>(sum) / image.size().area();
}

double variance(const cv::Mat& image, const double medium)
{
    double sum{};
    for (size_t i{}; i < image.size().height; ++i)
    {
        for (size_t j{}; j < image.size().width; ++j)
        {
            double delta{ image.at<uchar>(i, j) - medium };
            sum += pow(delta, 2.0);
        }
    }
    return sum / image.size().area();
}

double variance(const cv::Mat& image)
{
    double medium_{ medium(image) };
    double sum{};
    for (size_t i{}; i < image.size().height; ++i)
    {
        for (size_t j{}; j < image.size().width; ++j)
        {
            double delta{ image.at<uchar>(i, j) - medium_ };
            sum += pow(delta, 2.0);
        }
    }
    return sum / image.size().area();
}

double covariance(const cv::Mat& image1, const cv::Mat& image2, const double medium1, const double medium2)
{
    if (image1.size() == image2.size())
    {
        double sum{};
        for (size_t i{}; i < image1.size().height; ++i)
        {
            for (size_t j{}; j < image1.size().width; ++j)
            {
                double delta1{ image1.at<uchar>(i, j) - medium1 };
                double delta2{ image2.at<uchar>(i, j) - medium2 };
                sum += delta1 * delta2;
            }
        }
        return sum / image1.size().area();
    }
    else
    {
        throw "The images have different size";
    }
}

double covariance(const cv::Mat& image1, const cv::Mat& image2)
{
    if (image1.size() == image2.size())
    {
        double medium1{ medium(image1) };
        double medium2{ medium(image2) };
        double sum{};
        for (size_t i{}; i < image1.size().height; ++i)
        {
            for (size_t j{}; j < image1.size().width; ++j)
            {
                double delta1{ image1.at<uchar>(i, j) - medium1 };
                double delta2{ image2.at<uchar>(i, j) - medium2 };
                sum += delta1 + delta2;
            }
        }
        return sum / image1.size().area();
    }
    else
    {
        throw "The images have different size";
    }
}
