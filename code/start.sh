g++ `pkg-config --cflags opencv` blurSecuencial.cpp `pkg-config --libs opencv` -o blurSecuencial.out -lpthread
g++ `pkg-config --cflags opencv` blurParalelo.cpp `pkg-config --libs opencv` -o blurParalelo.out -lpthread

echo "                                                                  " >> mediciones.txt
echo "__      _                         ___ _ _       _                 " >> mediciones.txt
echo "/ _\ ___(_) ___ _ __   ___ ___    / __(_) |_ ___| |__   ___  ___  " >> mediciones.txt
echo "\ \ / __| |/ _ \ '_ \ / __/ _ \  /__\// | __/ __| '_ \ / _ \/ __| " >> mediciones.txt
echo "_\ \ (__| |  __/ | | | (_|  __/ / \/  \ | || (__| | | |  __/\__ \ " >> mediciones.txt
echo "\__/\___|_|\___|_| |_|\___\___| \_____/_|\__\___|_| |_|\___||___/ " >> mediciones.txt
echo "                                                                  " >> mediciones.txt

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
    echo "Usando un kernel de" $kernel >> mediciones.txt
    kernel=$[$kernel+1]
    # { time ./blurParalelo.out img1.jpg $kernel 1 >/dev/null 2>&1; } 2>> mediciones.txt
    #./blurParalelo.out img1.jpg $kernel
done

#Mediciones del programa paralelizado para kernel entre 3 y 16 con variacion de 1
echo "" >> mediciones.txt
echo "**********************************" >> mediciones.txt
echo "----------------------------------" >> mediciones.txt
echo "          Paralelizado            " >> mediciones.txt
echo "----------------------------------" >> mediciones.txt
echo "**********************************" >> mediciones.txt
 
kernel=3

echo "----------------------------------" >> mediciones.txt
echo "             img1                 " >> mediciones.txt
echo "----------------------------------" >> mediciones.txt

while [ $kernel -lt 16 ];
    do
    echo "Usando un kernel de" $kernel >> mediciones.txt
    kernel=$[$kernel+1]
    # { time ./blurParalelo.out img1.jpg $kernel 1 >/dev/null 2>&1; } 2>> mediciones.txt
    #./blurParalelo.out img1.jpg $kernel
done

#./blurParalelo.out img1.jpg 1 3