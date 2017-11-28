nvcc blur-effect.cu `pkg-config --cflags --libs opencv` -o blur-effect.out
TIMEFORMAT=%R

echo "" > mediciones.txt

#Mediciones del programa secuencial para kernel entre 3 y 16 con variacion de 1
echo "**********************************" >> mediciones.txt
echo "----------------------------------" >> mediciones.txt
echo "             Secuencial           " >> mediciones.txt
echo "----------------------------------" >> mediciones.txt
echo "**********************************" >> mediciones.txt


echo "----------------------------------" >> mediciones.txt
echo "         img1 720p                " >> mediciones.txt
echo "----------------------------------" >> mediciones.txt
echo -e "Kernel\tTime" >> mediciones.txt
kernel=3
while [ $kernel -lt 16 ]
    do
    echo -ne $kernel "\t" >> mediciones.txt
    { time ./blur-effect.out img1.jpg $kernel 1 1>/dev/null 2>&1; } 2>> mediciones.txt
    kernel=$[$kernel+2]
done


echo "----------------------------------" >> mediciones.txt
echo "          img2 1080p              " >> mediciones.txt
echo "----------------------------------" >> mediciones.txt
echo -e "Kernel\tTime" >> mediciones.txt
kernel=3
while [ $kernel -lt 16 ]
    do
    echo -ne $kernel "\t" >> mediciones.txt
    { time ./blur-effect.out img2.jpg $kernel 1 1>/dev/null 2>&1; } 2>> mediciones.txt
    kernel=$[$kernel+2]
done


echo "----------------------------------" >> mediciones.txt
echo "          img3 4k                 " >> mediciones.txt
echo "----------------------------------" >> mediciones.txt
echo -e "Kernel\tTime" >> mediciones.txt
kernel=3
while [ $kernel -lt 16 ]
    do
    echo -ne $kernel "\t" >> mediciones.txt
    { time ./blur-effect.out img3.jpg $kernel 1 1>/dev/null 2>&1; } 2>> mediciones.txt
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
 

echo "----------------------------------" >> mediciones.txt
echo "          img1 720p               " >> mediciones.txt
echo "----------------------------------" >> mediciones.txt

kernel=3
threads=128
blocks=1

echo -e "Kernel\t\tBlocks\t\tThreads\t\tTime" >> mediciones.txt

while [ $kernel -lt 16 ]
do
	while [ $blocks -lt 5 ]
	do
		while [ $threads -lt 1025 ]
		do
			echo -ne $kernel "\t\t" >> mediciones.txt
			echo -ne $blocks "\t\t" >> mediciones.txt
		    echo -ne $threads "\t\t" >> mediciones.txt		    
		    { time ./blur-effect.out img1.jpg $kernel $threads $blocks >/dev/null 2>&1; } 2>> mediciones.txt
			threads=$[$threads+128]
		done
		blocks=$[$blocks+1]
		threads=128
	done
	kernel=$[$kernel+2]	
	blocks=1
done


echo "----------------------------------" >> mediciones.txt
echo "          img2 1080p              " >> mediciones.txt
echo "----------------------------------" >> mediciones.txt

kernel=3
threads=128
blocks=1

echo -e "Kernel\t\tBlocks\t\tThreads\t\tTime" >> mediciones.txt

while [ $kernel -lt 16 ]
do
	while [ $blocks -lt 5 ]
	do
		while [ $threads -lt 1025 ]
		do
			echo -ne $kernel "\t\t" >> mediciones.txt
			echo -ne $blocks "\t\t" >> mediciones.txt
		    echo -ne $threads "\t\t" >> mediciones.txt		    
		    { time ./blur-effect.out img2.jpg $kernel $threads $blocks>/dev/null 2>&1; } 2>> mediciones.txt
			threads=$[$threads+128]
		done
		blocks=$[$blocks+1]
		threads=128
	done
	kernel=$[$kernel+2]	
	blocks=1
done

echo "----------------------------------" >> mediciones.txt
echo "          img3 4k                 " >> mediciones.txt
echo "----------------------------------" >> mediciones.txt

kernel=3
threads=128
blocks=1

echo -e "Kernel\t\tBlocks\t\tThreads\t\tTime" >> mediciones.txt

while [ $kernel -lt 16 ]
do
	while [ $blocks -lt 5 ]
	do
		while [ $threads -lt 1025 ]
		do
			echo -ne $kernel "\t\t" >> mediciones.txt
			echo -ne $blocks "\t\t" >> mediciones.txt
		    echo -ne $threads "\t\t" >> mediciones.txt		    
		    { time ./blur-effect.out img3.jpg $kernel $threads $blocks>/dev/null 2>&1; } 2>> mediciones.txt
			threads=$[$threads+128]
		done
		blocks=$[$blocks+1]
		threads=128
	done
	kernel=$[$kernel+2]	
	blocks=1
done
