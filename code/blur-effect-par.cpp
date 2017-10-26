#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat image, result;
int height, width;
int kernel, num_threads;

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

void *blur( void *thread_id ){
    long id;
    id = (long) thread_id;

    int init = id*(height/num_threads);
    int ending = (id+1)*(height/num_threads);
    
    // Calculate pixel average for every pixel
    for( int i = init; i < ending; ++i ){
        for( int j = 0; j < width; ++j ){
            result.at<Vec3b>(i,j) = get_average(i, j);
        }
    }
}

int main(int argc, char** argv){

    if (argc != 4){
        printf("Use: ./test.out <img_path> <num_kernel> <num_thread>\n");
        return -1;
    }

    image = imread( argv[1], 1 );

    if ( !image.data ){
        printf("Image couldn't be read. \n");
        return -1;
    }

    kernel = atoi(argv[2]);
    num_threads = atoi(argv[3]);

    height = image.size().height;
    width = image.size().width;
    
    // Create result image with same dimensions
    result = Mat(height, width, CV_8UC3);
    
    // Create threads
    pthread_t threads[num_threads];
    int rc;

    for( int i = 0; i < num_threads; ++i ){
        rc = pthread_create( &threads[i], NULL, blur, reinterpret_cast<void *>(i));

        if (rc){
            cout << "Error: Thread can't be created, " << rc << endl;
            exit(-1);
        }
    }

    void *return_join;
    for( int i = 0; i < num_threads; i++ ) {
        rc = pthread_join( threads[i], &return_join );
        if(rc != 0) {
            cout << "pthread_join failed";
            exit(EXIT_FAILURE);
        }
    }

    // Titles of images
    string original_window = "Original image";
    string result_window = "Blurred image";

    // Show original image
    namedWindow(original_window, WINDOW_AUTOSIZE);
    imshow(original_window, image);

    // Show resulting image
    namedWindow(result_window, WINDOW_AUTOSIZE);
    imshow(result_window, result);

    waitKey(0);
    pthread_exit(NULL);
    return 0;
}
