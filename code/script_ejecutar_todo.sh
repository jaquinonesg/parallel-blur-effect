g++ `pkg-config --cflags opencv` blur-effect-sec.cpp `pkg-config --libs opencv` -o blurSecuencial.out -lpthread
g++ `pkg-config --cflags opencv` blur-effect-par.cpp `pkg-config --libs opencv` -o blurParalelo.out -lpthread

echo "" > mediciones.txt

#Mediciones del programa secuencial para kernel entre 3 y 16 con variacion de 1
echo "**********************************" >> mediciones.txt
echo "----------------------------------" >> mediciones.txt
echo "             Secuencial           " >> mediciones.txt
echo "----------------------------------" >> mediciones.txt
echo "**********************************" >> mediciones.txt

kernel=3

echo "----------------------------------" >> mediciones.txt
echo "         img1 720p                " >> mediciones.txt
echo "----------------------------------" >> mediciones.txt
while [ $kernel -lt 16 ];
    do
    echo "Usando un kernel de" $kernel >> mediciones.txt
    { time ./blurSecuencial.out img1.jpg $kernel >/dev/null 2>&1; } 2>> mediciones.txt
    kernel=$[$kernel+2]
done

kernel=3
echo " "
echo "----------------------------------" >> mediciones.txt
echo "          img2 1080p              " >> mediciones.txt
echo "----------------------------------" >> mediciones.txt
while [ $kernel -lt 16 ];
    do
    echo "Usando un kernel de" $kernel >> mediciones.txt
    { time ./blurSecuencial.out img2.jpg $kernel >/dev/null 2>&1; } 2>> mediciones.txt
    echo " "
    kernel=$[$kernel+2]
done

kernel=3
echo " "
echo "----------------------------------" >> mediciones.txt
echo "          img3 4k                 " >> mediciones.txt
echo "----------------------------------" >> mediciones.txt
while [ $kernel -lt 16 ];
    do
    echo "Usando un kernel de" $kernel >> mediciones.txt
    { time ./blurSecuencial.out img3.jpg $kernel >/dev/null 2>&1; } 2>> mediciones.txt
    echo " "
    kernel=$[$kernel+2]
done


##################################################################################################
##################################################################################################
########################################Paralelizada##############################################
##################################################################################################
##################################################################################################


#Mediciones del programa paralelizado para kernel entre 3 y 16 con variacion de 1
echo "" >> mediciones.txt
echo "**********************************" >> mediciones.txt
echo "----------------------------------" >> mediciones.txt
echo "          Paralelizado            " >> mediciones.txt
echo "----------------------------------" >> mediciones.txt
echo "**********************************" >> mediciones.txt
 
kernel=3
threads=2
echo "----------------------------------" >> mediciones.txt
echo "          img1 720p               " >> mediciones.txt
echo "----------------------------------" >> mediciones.txt

while [ $kernel -lt 16 ];
    do
	while [ $threads -lt 17 ];
        do
        echo "Usando una cantidad de hilos de" $threads >> mediciones.txt
        echo "Usando un kernel de" $kernel >> mediciones.txt
        { time ./blurParalelo.out img1.jpg $kernel $threads >/dev/null 2>&1; } 2>> mediciones.txt
	threads=$[$threads*2]
    done
    kernel=$[$kernel+2]
    threads=2
done

kernel=3
threads=2
echo "----------------------------------" >> mediciones.txt
echo "          img2 1080p              " >> mediciones.txt
echo "----------------------------------" >> mediciones.txt

while [ $kernel -lt 16 ];
    do
	while [ $threads -lt 17 ];
        do
        echo "Usando una cantidad de hilos de" $threads >> mediciones.txt
        echo "Usando un kernel de" $kernel >> mediciones.txt
        { time ./blurParalelo.out img2.jpg $kernel $threads >/dev/null 2>&1; } 2>> mediciones.txt
	threads=$[$threads*2]
    done
    kernel=$[$kernel+2]
    threads=2
done

kernel=3
threads=2
echo "----------------------------------" >> mediciones.txt
echo "          img3 4k                 " >> mediciones.txt
echo "----------------------------------" >> mediciones.txt

while [ $kernel -lt 16 ];
    do
	while [ $threads -lt 17 ];
        do
        echo "Usando una cantidad de hilos de" $threads >> mediciones.txt
        echo "Usando un kernel de" $kernel >> mediciones.txt
        { time ./blurParalelo.out img3.jpg $kernel $threads >/dev/null 2>&1; } 2>> mediciones.txt
	threads=$[$threads*2]
    done
    kernel=$[$kernel+2]
    threads=2
done
