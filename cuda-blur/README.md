### DESCRIPCIÓN
El programa implementa un algoritmo que paraleliza la aplicación del efecto borroso (blur) con un kernel cambiante sobre imágenes de diferente calidad. Se implementa usando la GPU con CUDA.

### COMPILACIÓN
```shell
nvcc blur-effect.cu `pkg-config --cflags --libs opencv` -o blur-effect.out
```

### EJECUCIÓN
```shell
./blur-effect.out <img-path> <num-kernel> <num-threads> <num-blocks>
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
