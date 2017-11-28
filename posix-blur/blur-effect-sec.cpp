#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat image, result;
int height, width;
int kernel;

/**
* image: Image to be blurred
* i: Pixel position y
* j: Pixel position x
* return average channel vector
**/

Vec3b get_average( const int &y, const int &x ){
    int blue, green, red, dy, dx, cont, limit;
    blue = green = red = cont = 0;
    
    // Limit of adjacent positions
    limit = kernel/2;

    // Traverse all adjacents positions
    for( int i = -limit; i <= limit; ++i ){
        for( int j = -limit; j <= limit; ++j ){
            dy = y + i;
            dx = x + j;

            // Verify if point is inside of image
            if( 0 <= dy && dy < height && 0 <= dx && dx < width ){
                blue += image.at<Vec3b>(dy, dx)[0];
                green += image.at<Vec3b>(dy, dx)[1];
                red += image.at<Vec3b>(dy, dx)[2];
                ++cont;
            }
        }
    }

    // Calculate average of each channel
    blue /= cont;
    green /= cont;
    red /= cont;

    return Vec3b(blue, green, red);
}

void blur(){    
    // Calculate pixel average for every pixel
    for( int i = 0; i < height; ++i ){
        for( int j = 0; j < width; ++j ){
            result.at<Vec3b>(i,j) = get_average(i, j);
        }
    }
}

int main(int argc, char** argv){

    if (argc != 3){
        printf("Use: ./blurSecuencial.out <img_path> <num_kernel>\n");
        return -1;
    }

    image = imread( argv[1], 1 );

    if ( !image.data ){
        printf("Image couldn't be read. \n");
        return -1;
    }

    kernel = atoi(argv[2]);

    height = image.size().height;
    width = image.size().width;
    
    // Create result image with same dimensions
    result = Mat(height, width, CV_8UC3);
    
    blur();

    string file_name;
    file_name = "blurred-";
    file_name += argv[1];
    imwrite(file_name, result);

    // waitKey(0);
    return 0;
}
