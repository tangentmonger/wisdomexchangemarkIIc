#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>

#include "Wisdom.h"

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        std::cout<<"usage: DisplayImage.out <Image_Path>\n";
        return -1;
    }

    char* filepath = argv[1];
    Wisdom aWisdom(filepath);
    
    cv::namedWindow("Display Image", cv::WINDOW_NORMAL);
    //cv::imshow("Display Image", *aWisdom.getOriginal());
    //cv::waitKey(0);
    //cv::imshow("Display Image", *aWisdom.getPrepared());
    //cv::waitKey(0);
    cv::imshow("Display Image", *aWisdom.getHoughLines());
    cv::waitKey(0);
       
    return 0;
}


