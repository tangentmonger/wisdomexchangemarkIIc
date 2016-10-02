#ifndef WISDOM_H
#define WISDOM_H

#include <string>
#include <opencv2/opencv.hpp>

class Wisdom
{
    public:
        Wisdom(char* thefilepath);
        ~Wisdom();
        cv::Mat getOriginal();
        char* getFilepath();

    protected:
        char* filepath;
        cv::Mat original;
};
#endif
