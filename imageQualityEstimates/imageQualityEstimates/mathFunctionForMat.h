#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

double medium(const cv::Mat& image);

double variance(const cv::Mat& image, const double medium);

double variance(const cv::Mat& image);

double covariance(const cv::Mat& image1, const cv::Mat& image2, const double medium1, const double medium2);

double covariance(const cv::Mat& image1, const cv::Mat& image2);
