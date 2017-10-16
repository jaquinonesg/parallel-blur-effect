#include <opencv2/opencv.hpp>


int main(int argc, char* argv[])
{

    IplImage* img = cvLoadImage("img.jpg",0);
    IplImage* dst = cvCloneImage(img);
    int height,width,step,channels;
    int height2,width2,step2,channels2;

    height = img->height;
    width = img->width;
    step = img->widthStep;
    channels = img->nChannels;
    uchar* data = (uchar *)img->imageData;

    height2    = dst->height; // row
    width2     = dst->width; // col
    step2      = dst->widthStep; // size of aligned image row in bytes
    channels2  = dst->nChannels; 
    uchar* dstData      = (uchar *)dst->imageData;
    int total = 0;
    int i,j,x,y,tx,ty;
    //blur
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {   
            int ksize=3;
            total=0;
            for (x = -ksize/2; x <=ksize/2; x++)
                for (y = -ksize/2; y <=ksize/2; y++)
                {
                    tx=i+x;
                    ty=j+y;
                    if(tx>=0&&tx<height && ty>=0 && ty<width)
                    {
                        total+=data[tx*step+ty];
                    }
                }

            dstData[i*step+j] = total/ksize/ksize;
        }
    }
    cvShowImage("img",img);
    cvShowImage("dst",dst);
    cvWaitKey(0);
}