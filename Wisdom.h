#ifndef WISDOM_H
#define WISDOM_H

#include <string>
#include <opencv2/opencv.hpp>

// Represents one piece of wisdom and handles operations on it.
class Wisdom
{
    public:
        // Constructor. Supply the path to the image of the wisdom.
        Wisdom(char* thefilepath);

        // Destructor.
        ~Wisdom();

        // Get the filepath to the wisdom image.
        char* getFilepath();

        // Load and return the original wisdom image.
        cv::Mat getOriginal();

        // Load and return the prepared wisdom image (scaled, thresholded
        // and inverted to give a white-on-black image ready for further
        // image operations).
        cv::Mat getPrepared();

    protected:
        char* filepath;
        cv::Mat original;
        cv::Mat prepared;
};
#endif
