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
    Wisdom one_wisdom(filepath);
    
    cv::Mat image;
    image = cv::imread( argv[1], 1 );
    
    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE );
    cv::imshow("Display Image", one_wisdom.get_original());
    cv::waitKey(0);
       
    return 0;
}


