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

char* Wisdom::getFilepath()
{
    return filepath;
}

cv::Mat Wisdom::getOriginal()
{
    //todo: caching
    original = cv::imread(filepath, 1);
    return original;
}


