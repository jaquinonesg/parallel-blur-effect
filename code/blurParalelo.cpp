#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <pthread.h>

using namespace cv;
using namespace std;


// Adjacent positions
int dj[] = {0,1,0,-1,0,-1,-1,1,1};
int di[] = {-1,0,1,0,0,-1,1,-1,1};

int kernel, NUM_THREADS;
Mat image, imageFiltered, result;

struct The_Struct {
    int init, ending, height, width, threadid;
};

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

void *blur(void *threadid) {
    long id;
    id = (long)threadid;
    int width=image.cols;
    int height=image.rows;
    for (int i=(id*(height/NUM_THREADS)); i<(id+1)*(height/NUM_THREADS); i++){
          for (int j=0; j<width; j++){
              int aux_r=0;	//2
              int aux_g=0;	//1
              int aux_b=0;	//0
              int aux_div=1;
              for (int a=1; a<=kernel; a++){
                  if(!(i-a<0)){
                      aux_r+= image.at<cv::Vec3b>(i-a,j)[2];
                      aux_g+= image.at<cv::Vec3b>(i-a,j)[1];
                      aux_b+= image.at<cv::Vec3b>(i-a,j)[0];
                      aux_div++;
                  }
                  if(i+a<height){
                      aux_r+= image.at<cv::Vec3b>(i+a,j)[2];
                      aux_g+= image.at<cv::Vec3b>(i+a,j)[1];
                      aux_b+= image.at<cv::Vec3b>(i+a,j)[0];
                      aux_div++;
                  }
                  if(!(j-a<0)){
                      aux_r+= image.at<cv::Vec3b>(i,j-a)[2];
                      aux_g+= image.at<cv::Vec3b>(i,j-a)[1];
                      aux_b+= image.at<cv::Vec3b>(i,j-a)[0];
                      aux_div++;
                  }
                  if(j+a<width){
                      aux_r+= image.at<cv::Vec3b>(i,j+a)[2];
                      aux_g+= image.at<cv::Vec3b>(i,j+a)[1];
                      aux_b+= image.at<cv::Vec3b>(i,j+a)[0];
                      aux_div++;
                  }
              }
       imageFiltered.at<cv::Vec3b>(i,j)[2]=(image.at<cv::Vec3b>(i,j)[2]+aux_r)/(aux_div);
       imageFiltered.at<cv::Vec3b>(i,j)[1]=(image.at<cv::Vec3b>(i,j)[1]+aux_g)/(aux_div);
       imageFiltered.at<cv::Vec3b>(i,j)[0]=(image.at<cv::Vec3b>(i,j)[0]+aux_b)/(aux_div);
     }
   }
   pthread_exit(NULL);
 }

int main(int argc, char** argv){

    if (argc != 4){ printf("Uso: ./blurParalelo.out <ruta_imagen> <numero_hilos> <numero_kernel>\n");    return -1; }
    image = imread( argv[1], 1 );
    imageFiltered = imread( argv[1], 1 );
    if ( !image.data ){ printf("No se pudo leer la imagen. \n");    return -1;  }
    NUM_THREADS = atoi(argv[2]);
    pthread_t threads[NUM_THREADS];
    kernel = atoi(argv[3]);

    int h = image.size().height;
    int w = image.size().width;

    // Create result image with same dimensions
    result = Mat(h, w, CV_8UC3);

    int inc, init, ending, rc;
    inc = h / NUM_THREADS;
    init = 0;

    The_Struct sniff;
    sniff.init = 0;
    sniff.width = w;

    for( int i = 0; i < NUM_THREADS; i++ ) {
        sniff.ending = init + inc;
        sniff.threadid;
        //si se pretende usar la estructura se pasa en el segundo parametro, no al final
        //rc = pthread_create(&threads[i], NULL, solve, (void *) &sniff );
        rc = pthread_create(&threads[i], NULL, blur, reinterpret_cast<void *>(i));

        if (rc) {   cout << "Error: no se puede crear hilo," << rc << endl; exit(-1);   }
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
    //imshow(result_window, result);
    imshow(result_window, imageFiltered);

    waitKey(0);
    pthread_exit(NULL);
    return 0;
}
