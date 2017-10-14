#include <stdio.h>
#include <opencv/cvaux.h>
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <opencv/cv.h>
#include <stdlib.h>
#include <time.h>
#include <vector>


int w=0;
int h=0;
int channels=0;

int main(int argc, char* argv[])
{
  IplImage* img = cvLoadImage("xxx.jpg");
  int Ksize=
  Mat m = cv::cvarrToMat(img);
  CvSize dim = cvGetSize(img);
  h=dim.height;
  w=dim.width;
  channels=img->nChannels;


  if (!img)
  {
    printf("Image can NOT Load!!!\n");
    return 1;
  }

  
  int sumB=0;
  int sumG=0;
  int sumR=0;
  int deno=8;

  for (int i = 1; i < h-1; ++i)
  {
  	for (int j = 1; j < w-1; ++j)
  	{
  		sumB=0;
  		sumG=0;
  		sumR=0;
  		sumB+=(m.at<cv::Vec3b>(i-1,j-1)[0] );
  		sumB+=(m.at<cv::Vec3b>(i-1,j)[0] );
  		sumB+=(m.at<cv::Vec3b>(i-1,j+1)[0] );
  		sumB+=(m.at<cv::Vec3b>(i,j-1)[0] );
  		sumB+=(m.at<cv::Vec3b>(i,j+1)[0] );
  		sumB+=(m.at<cv::Vec3b>(i+1,j-1)[0] );
  		sumB+=(m.at<cv::Vec3b>(i+1,j)[0] );
  		sumB+=(m.at<cv::Vec3b>(i+1,j+1)[0] );
  	
  		m.at<cv::Vec3b>(i,j)[0] = sumB/deno;


  		sumG+=(m.at<cv::Vec3b>(i-1,j-1)[1] );
  		sumG+=(m.at<cv::Vec3b>(i-1,j)[1] );
  		sumG+=(m.at<cv::Vec3b>(i-1,j+1)[1] );
  		sumG+=(m.at<cv::Vec3b>(i,j-1)[1] );
  		sumG+=(m.at<cv::Vec3b>(i,j+1)[1] );
  		sumG+=(m.at<cv::Vec3b>(i+1,j-1)[1] );
  		sumG+=(m.at<cv::Vec3b>(i+1,j)[1] );
  		sumG+=(m.at<cv::Vec3b>(i+1,j+1)[1] );

  		m.at<cv::Vec3b>(i,j)[1] = sumG/deno;


  		sumR+=(m.at<cv::Vec3b>(i-1,j-1)[2] );
  		sumR+=(m.at<cv::Vec3b>(i-1,j)[2] );
  		sumR+=(m.at<cv::Vec3b>(i-1,j+1)[2] );
  		sumR+=(m.at<cv::Vec3b>(i,j-1)[2] );
  		sumR+=(m.at<cv::Vec3b>(i,j+1)[2] );
  		sumR+=(m.at<cv::Vec3b>(i+1,j-1)[2] );
  		sumR+=(m.at<cv::Vec3b>(i+1,j)[2] );
  		sumR+=(m.at<cv::Vec3b>(i+1,j+1)[2] );

		m.at<cv::Vec3b>(i,j)[2] = sumR/deno; 

  	}
  }
cv::imwrite( "tested720.jpg", m);


return 0;
}