#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <string.h>

using namespace cv;

__global__
void saxpy(int n, float a, float *x, float *y){
    int i = blockIdx.x*blockDim.x + threadIdx.x;
    if (i < n)
        y[i] = a*x[i] + y[i];
}

int main(int argc, char** argv){
    Mat image, result, *d_image, *d_result;
    int kernel;
    int height, width;

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

    // CUDA
    cudaMalloc(&d_image, sizeof(image));
    cudaMalloc(&d_result, sizeof(image));

    cudaMemcpy(d_image, &image, sizeof(image), cudaMemcpyHostToDevice);
    cudaMemcpy(d_result, &result, sizeof(image), cudaMemcpyHostToDevice);

    d_result = d_image;

    cudaMemcpy(&result, d_result, sizeof(image), cudaMemcpyDeviceToHost);

    cudaFree(d_image);
    cudaFree(d_result);

    ///////////////////////////////////////////

    int N = 1<<20;
    float *x, *y, *d_x, *d_y;
    x = (float*)malloc(N*sizeof(float));
    y = (float*)malloc(N*sizeof(float));

    cudaMalloc(&d_x, N*sizeof(float));
    cudaMalloc(&d_y, N*sizeof(float));

    for (int i = 0; i < N; i++) {
        x[i] = 1.0f;
        y[i] = 2.0f;
    }

    cudaMemcpy(d_x, x, N*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_y, y, N*sizeof(float), cudaMemcpyHostToDevice);

    // Perform SAXPY on 1M elements
    saxpy<<<(N+255)/256, 256>>>(N, 2.0f, d_x, d_y);

    cudaMemcpy(y, d_y, N*sizeof(float), cudaMemcpyDeviceToHost);

    float maxError = 0.0f;
    for (int i = 0; i < N; i++)
    maxError = max(maxError, abs(y[i]-4.0f));
    printf("Max error: %f\n", maxError);

    cudaFree(d_x);
    cudaFree(d_y);
    free(x);
    free(y);

    char file_name[12] = "blurred.jpg";
    imwrite(file_name, result);
}
