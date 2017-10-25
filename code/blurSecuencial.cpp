#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>
using namespace cv;

// Adjacent positions
int dj[] = {0,1,0,-1,0,-1,-1,1,1};
int di[] = {-1,0,1,0,0,-1,1,-1,1};

/**
* image: Image to be blurred
* i: Pixel position y
* j: Pixel position x
* return average channel vector
**/

Vec3b get_average( const Mat &image, const int &i, const int &j ){
    int h = image.size[0];
    int w = image.size[1];
    const int SIZE = sizeof(di) / sizeof(int);

    int b, g, r, ni, nj, c;
    b = g = r = c = 0;

    // Traverse all adjacents positions
    for( int k = 0; k < SIZE; ++k ){
        ni = i + di[k];
        nj = j + dj[k];

        // Verify if point is inside of image
        if( ni >= 0 && ni < h && nj >= 0 && nj < w ){
            b += image.at<Vec3b>(ni, nj)[0];
            g += image.at<Vec3b>(ni, nj)[1];
            r += image.at<Vec3b>(ni, nj)[2];
            ++c;
        }
    }

    // Calculate average of each channel
    b /= c;
    g /= c;
    r /= c;

    return Vec3b(b, g, r);
}

int main(int argc, char** argv){

    if (argc != 2){
        printf("Uso: ./test.out <ruta_imagen>\n");
        return -1;
    }

    Mat image, result;
    image = imread( argv[1], 1 );

    if ( !image.data ){
        printf("No se pudo leer la imagen. \n");
        return -1;
    }

    int h = image.size().height;
    int w = image.size().width;

    // Create result image with same dimensions
    result = Mat(h, w, CV_8UC3);


    // BGR
    int b, g, r;
    // Calculate pixel average for every pixel
    for( int i = 0; i < h; ++i ){
        for( int j = 0; j < w; ++j ){
            result.at<Vec3b>(i,j) = get_average(image, i, j);
        }
    }

    std::string original_window = "El Momo";
    std::string result_window = "El Otro Momo";

    // Show original image
    namedWindow(original_window, WINDOW_AUTOSIZE);
    imshow(original_window, image);

    // Show resulting image
    namedWindow(result_window, WINDOW_AUTOSIZE);
    moveWindow(result_window, w + 100, 0);
    imshow(result_window, result);

    waitKey(0);
    return 0;
}
