g++ `pkg-config --cflags opencv` blurSecuencial.cpp `pkg-config --libs opencv` -o blurSecuencial.out -lpthread
g++ `pkg-config --cflags opencv` blurParalelo.cpp `pkg-config --libs opencv` -o blurParalelo.out -lpthread

echo "Mediciones en archivo mediciones.txt"
echo "Imagen1" > mediciones.txt

echo "                                                                  "
echo "__      _                         ___ _ _       _                 "
echo "/ _\ ___(_) ___ _ __   ___ ___    / __(_) |_ ___| |__   ___  ___  "
echo "\ \ / __| |/ _ \ '_ \ / __/ _ \  /__\// | __/ __| '_ \ / _ \/ __| "
echo "_\ \ (__| |  __/ | | | (_|  __/ / \/  \ | || (__| | | |  __/\__ \ "
echo "\__/\___|_|\___|_| |_|\___\___| \_____/_|\__\___|_| |_|\___||___/ "
echo "                                                                  "

#Mediciones del programa secuencial para kernel entre 3 y 16 con variacion de 1
echo "**********************************" >> mediciones.txt
echo "----------------------------------" >> mediciones.txt
echo "             Secuencial           " >> mediciones.txt
echo "----------------------------------" >> mediciones.txt
echo "**********************************" >> mediciones.txt

kernel=3

echo "----------------------------------" >> mediciones.txt
echo "             img1                 " >> mediciones.txt
echo "----------------------------------" >> mediciones.txt

while [ $kernel -lt 16 ];
    do
    echo "Usando un kernel de" $kernel >> 
    #./blurParalelo.out img1.jpg kernel
    kernel=$[$kernel+1]
done

#Mediciones del programa paralelizado para kernel entre 3 y 16 con variacion de 1
echo "**********************************" >> mediciones.txt
echo "----------------------------------" >> mediciones.txt
echo "          Paralelizado            " >> mediciones.txt
echo "----------------------------------" >> mediciones.txt
echo "**********************************" >> mediciones.txt
 
kernel=3
while [ $kernel -lt 16 ];
    do
    kernel=$[$kernel+1]
    ./blurParalelo.out img1.jpg kernel
done

#./blurParalelo.out img1.jpg 1 3
