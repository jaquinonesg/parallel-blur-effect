#include <stdio.h>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(){
    
    IplImage* img = cvLoadImage("img.jpg", CV_LOAD_IMAGE_COLOR);
    Mat m = cv::cvarrToMat(img);
    CvSize dim = cvGetSize(img);
    int h = dim.height;
    int w = dim.width;

  
    
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            printf("%d", m.at<Vec3b>(i,j)[0]);
            printf("%d", m.at<Vec3b>(i,j)[1]);
            printf("%d", m.at<Vec3b>(i,j)[2]);
        }
    }
    return 0;

}
