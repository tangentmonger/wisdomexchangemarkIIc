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

char* Wisdom::get_filepath()
{
    return filepath;
}

cv::Mat Wisdom::get_original()
{
    //todo: caching
    original = cv::imread(filepath, 1);
    return original;
}


