### DESCRIPCIÓN
El programa implementa un algoritmo que paraleliza la aplicación del efecto borroso (blur) con un kernel cambiante sobre imágenes de diferente calidad utilizando las librerías POSIX para el manejo de hilos y OpenCV para el manejo de imágenes.

### COMPILACIÓN
```shell
g++ `pkg-config --cflags opencv` -fopenmp blur-effect-mp.cpp `pkg-config --libs opencv` -o blur-effect-mp.out
```

### EJECUCIÓN
```shell
././blur-effect-mp.out <img-path> <num-kernel>
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
