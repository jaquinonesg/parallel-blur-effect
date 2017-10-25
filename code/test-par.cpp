#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <pthread.h>

using namespace cv;
using namespace std;

#define NUM_THREADS 4

// Adjacent positions
int dj[] = {0,1,0,-1,0,-1,-1,1,1};
int di[] = {-1,0,1,0,0,-1,1,-1,1};

Mat image, result;

struct The_Struct {
    int init, ending, height, width, threadid;
};

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

void *solve( void *pointer ){
    // BGR
    int b, g, r;
    struct The_Struct *sniff;
    sniff = (The_Struct *) pointer;

    // Calculate pixel average for every pixel
    for( int i = sniff->init; i < sniff->ending; ++i ){
        for( int j = 0; j < sniff->width; ++j ){
            result.at<Vec3b>(i,j) = get_average(image, i, j);
        }
    }

    long tid;
    tid = sniff->threadid;
    cout << "Hello World! Thread ID, " << tid << endl;    
}

int main(int argc, char** argv){
    if (argc != 2){
        printf("Uso: ./test.out <ruta_imagen>\n");
        return -1;
    }

    image = imread( argv[1], 1 );

    if ( !image.data ){
        printf("No se pudo leer la imagen. \n");
        return -1;
    }

    int h = image.size().height;
    int w = image.size().width;

    // Create result image with same dimensions
    result = Mat(h, w, CV_8UC3);


    pthread_t threads[NUM_THREADS];

    int inc, init, ending, rc;
    inc = h / NUM_THREADS;
    init = 0;

    The_Struct sniff;
    sniff.init = 0;
    sniff.width = w;

    for( int i = 0; i < NUM_THREADS; i++ ) {
        sniff.ending = init + inc;
        sniff.threadid;

        rc = pthread_create(&threads[i], NULL, solve, (void *) &sniff );

        if (rc) {
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }

        init = ending;
    }    

    // Titles of images
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
    pthread_exit(NULL);
    return 0;
}
