# g++ `pkg-config --cflags opencv` test.cpp `pkg-config --libs opencv` -o test.out
g++ `pkg-config --cflags opencv` blurParalelo.cpp `pkg-config --libs opencv` -o blurParalelo.out -lpthread
./blurParalelo.out img1.jpg 1 3