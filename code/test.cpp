#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;

int main(int argc, char** argv)
{
    if ( argc != 2)
    {
        printf("Uso: ./test.out <ruta_imagen>\n");
        return -1;
    }
    Mat image;
    image = imread( argv[1], 1 );

    if ( !image.data )
    {
        printf("Y la imagen? \n");
        return -1;
    }
    namedWindow("El Momo", WINDOW_AUTOSIZE);
    imshow("El Momo", image);
    waitKey(0);
    return 0;
}