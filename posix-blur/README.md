### DESCRIPCIÓN
El programa implementa un algoritmo que paraleliza la aplicación del efecto borroso (blur) con un kernel cambiante sobre imágenes de diferente calidad utilizando las librerías POSIX para el manejo de hilos y OpenCV para el manejo de imágenes.

### COMPILACIÓN
```shell
g++ `pkg-config --cflags opencv` blur-effect-sec.cpp `pkg-config --libs opencv` -o sequencial-blur.out -lpthread
g++ `pkg-config --cflags opencv` blur-effect-par.cpp `pkg-config --libs opencv` -o parallel-blur.out -lpthread
```

### EJECUCIÓN
```shell
./sequencial-blur.out <img-path> <num-kernel>
./parallel-blur.out <img-path> <num-kernel> <num-threads>
```

### LIBRERÍAS
Las librerías utilizadas por el programa son las siguientes:
```c++  
#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>
```

### CONTACTO

#### Desarrolladores:
* Laura Viviana Álvarez Carvajal       - lvalvarezc@unal.edu.co
* Jorge Alexander Quiñones Garcia      - jaquinonesg@unal.edu.co
