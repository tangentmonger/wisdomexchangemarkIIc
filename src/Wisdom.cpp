#include "Wisdom.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <math.h>
#include <list>

#define INK_THRESHOLD 100

// Constructor. Provide path to wisdom image.
Wisdom::Wisdom(std::string thefilepath)
{
    filepath = thefilepath;
}

Wisdom::~Wisdom()
{
}

// Return the path to the wisdom image.
std::string Wisdom::getFilepath()
{
    return filepath;
}

// Load and return the loaded wisdom image (greyscale).
cv::Mat * Wisdom::getOriginal()
{
    // Cache the image once loaded.
    if(original.empty())
    {
        char * path = const_cast<char*>(filepath.c_str());
        original = cv::imread(path, CV_LOAD_IMAGE_GRAYSCALE);
    }
    return &original;
}

// Return a 10% sized, thresholded (white on black) version of the wisdom image.
cv::Mat * Wisdom::getPrepared()
{
    // Cache the image once generated.
    if(prepared.empty())
    {
        prepared = getOriginal()->clone();
        // Resize to 10% of original size, so that later operations are faster
        cv::resize(prepared, prepared, cv::Size(), 0.1, 0.1, cv::INTER_AREA);
        // Threshold and invert: pixels darker than threshold become white and
        // vice versa
        int THRESHOLD = 230;
        cv::threshold(prepared, prepared, THRESHOLD, 255, cv::THRESH_BINARY_INV);
    }
    return &prepared;

}

// Return true if this wisdom is blank (i.e. ink is below threshold)
bool Wisdom::isBlank()
{
    //TODO: cache result maybe
    double ink = cv::countNonZero(*getPrepared());
    return (ink < INK_THRESHOLD);
}

int Wisdom::angle()
{
    int angle = 0;
    int MUL = 5;
    int RHO = 1; // resolution in pixels
    float THETA = 3.142 / 180 ; //resolution in radians
    int THRESHOLD = 150;
    int MIN_LINES = 45;

    houghLines = getPrepared()->clone();
    
    std::vector<cv::Vec2f> lines;
    // keep reducing the threshold and running Hough until we get at least
    // 50 lines back, then calculate the most common angle by
    // splitting up angles into buckets and taking the largest bucket
    for(int threshold = THRESHOLD; threshold >= 0; threshold--){
        cv::HoughLines(houghLines, lines, RHO, THETA, threshold);
        int nLines = lines.size();
        if(nLines > MIN_LINES){
            // initialise buckets
            const int BUCKETSIZE_D=5;
            const float BUCKETSIZE_R = BUCKETSIZE_D* 3.142/180;
            const int N_BUCKETS = floor(180 / BUCKETSIZE_D);
            int bucket[N_BUCKETS];

            for(int i=0; i<N_BUCKETS; i++){
                bucket[i] = 0;
            }

            // count lines in each bucket
            for (int i=0; i< nLines; i++){
                float angle = lines[i][1];
                int bucket_index = floor(angle / BUCKETSIZE_R);
                bucket[(bucket_index % N_BUCKETS)]++; //take care of wrapping around 360 degrees
            }

            // get the best bucket
            int best_bucket = 0;
            for(int i=0; i<N_BUCKETS; i++){
                if(bucket[i] > bucket[best_bucket]){
                    best_bucket = i;
                }
            }

            // calculate angle from the best bucket
            float theta = (best_bucket) * BUCKETSIZE_R;
            angle = (int)(90 - (theta * 180/3.142));

            break;
        }
    }
    return angle;
}

cv::Mat * Wisdom::getHoughLines()
{
    // Cache the image once generated.
    if(houghLines.empty())
    {
        int MUL = 5;
        int RHO = 1; // resolution in pixels
        float THETA = 3.142 / 180 ; //resolution in radians
        int THRESHOLD = 150;

        houghLines = getPrepared()->clone();
        
        std::vector<cv::Vec2f> lines;
        // keep reducing the threshold and running Hough until we get at least
        // 50 lines back, then calculate the most common angle by
        // splitting up angles into buckets and taking the largest bucket
        for(int threshold = THRESHOLD; threshold >= 0; threshold--){
            cv::HoughLines(houghLines, lines, RHO, THETA, threshold);
            int nLines = lines.size();
            if(nLines > 50){
                // initialise buckets
                const int BUCKETSIZE_D=5;
                const float BUCKETSIZE_R = BUCKETSIZE_D* 3.142/180;
                const int N_BUCKETS = floor(180 / BUCKETSIZE_D);
                int bucket[N_BUCKETS];

                for(int i=0; i<N_BUCKETS; i++){
                    bucket[i] = 0;
                }

                // count lines in each bucket
                for (int i=0; i< nLines; i++){
                    float angle = lines[i][1];
                    int bucket_index = floor(angle / BUCKETSIZE_R);
                    bucket[(bucket_index % N_BUCKETS)]++; //take care of wrapping around 360 degrees
                }

                // get the best bucket
                int best_bucket = 0;
                for(int i=0; i<N_BUCKETS; i++){
                    if(bucket[i] > bucket[best_bucket]){
                        best_bucket = i;
                    }
                }

                // calculate angle from the best bucket
                float theta = (best_bucket) * BUCKETSIZE_R;
                float rho = 100; //dont' care, just want the angle
                int angle = (int)(90 - (theta * 180/3.142));
                std::cout<<"angle: "<<angle<<"\n";

                double a = cos(theta), b = sin(theta);
                double x0 = a*rho, y0 = b*rho;
                cv::Point pt1(floor(x0 + 1000*(-b)),
                        floor(y0 + 1000*(a)));
                cv::Point pt2(floor(x0 - 1000*(-b)),
                        floor(y0 - 1000*(a)));
                cv::line(houghLines, pt1, pt2, 128, 1, 8 );
                break;
            }
        }
    }
    return &houghLines;

}

