#include "Wisdom.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

Wisdom::Wisdom(char* thefilepath)
{
    filepath = thefilepath;
}

Wisdom::~Wisdom()
{
}

char * Wisdom::getFilepath()
{
    return filepath;
}

cv::Mat * Wisdom::getOriginal()
{
    // Cache the image once loaded.
    if(original.empty())
    {
        original = cv::imread(filepath, 1);
    }
    return &original;
}

cv::Mat * Wisdom::getPrepared()
{
    // Cache the image once generated.
    if(prepared.empty())
    {
        prepared = getOriginal()->clone();
        // Convert to B&W
        cv::cvtColor(prepared, prepared, cv::COLOR_BGR2GRAY);
        // Resize to 10% of original size, so that later operations are faster
        cv::resize(prepared, prepared, cv::Size(), 0.1, 0.1, cv::INTER_AREA);
        // Threshold and invert: pixels darker than threshold become white and
        // vice versa
        int THRESHOLD = 230;
        cv::threshold(prepared, prepared, THRESHOLD, 255, cv::THRESH_BINARY_INV);
    }
    return &prepared;

}


