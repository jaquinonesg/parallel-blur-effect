# g++ `pkg-config --cflags opencv` test.cpp `pkg-config --libs opencv` -o test.out
g++ `pkg-config --cflags opencv` test-par.cpp `pkg-config --libs opencv` -o test.out -lpthread