#ifndef WISDOM_H
#define WISDOM_H

#include <string>
#include <opencv2/opencv.hpp>

class Wisdom
{
    public:
        Wisdom(char* thefilepath);
        ~Wisdom();
        cv::Mat get_original();
        char* get_filepath();

    protected:
        char* filepath;
        cv::Mat original;
};
#endif
