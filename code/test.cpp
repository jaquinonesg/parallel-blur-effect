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

    Mat image, result;
    image = imread( argv[1], 1 );

    int h = image.size[0];
    int w = image.size[1];

    result = Mat(h, w, CV_8UC3);

    printf("%d\n", h);
    printf("%d\n", w);

    if ( !image.data )
    {
        printf("Y la imagen? \n");
        return -1;
    }

    namedWindow("El Momo", WINDOW_AUTOSIZE);
    imshow("El Momo", image);

    // BGR
    int b, g, r;
    for( int i = 0; i < h; ++i ){
        for( int j = 0; j < w; ++j ){
            b = image.at<Vec3b>(i,j)[0];
            g = image.at<Vec3b>(i,j)[1];
            r = image.at<Vec3b>(i,j)[2];

            // Copy to result
            result.at<Vec3b>(i,j) = Vec3b(b, g, r);

            printf("%d ",  b);
            printf("%d ",  g);
            printf("%d\n", r);
        }
    }

    namedWindow("El Otro Momo", WINDOW_AUTOSIZE);
    imshow("El Otro Momo", result);

    waitKey(0);
    return 0;
}
