#!/bin/bash
# By glagan (ncolomer) and slightly modified by myself (Volt - marandre)
rm -f micro_paint gen
gcc -Wall -Wextra -Werror -lm micro_paint.c -o micro_paint
gcc -Wall -Wextra -Werror -lm our_micro_paint.c -o _our_micro_paint
g++ -Wall -Wextra -Werror generate_example.cpp -o gen
counter=0
max=1000
our_res=-1
bad_res=-1
while [ $counter -le $max ]
do
	./gen
	if [ $? ]
	then
		sleep .01
		./_our_micro_paint example_ > coutput 2>&1
		our_res=$?
		./micro_paint example_ > output 2>&1
		bad_res=$?
		if [ $our_res -ne $bad_res ]
		then
			printf "\n: different return result, our \e[1;31m$our_res\e[0m and yours \e[1;32m$bad_res\e[0m !\n"
			exit 1
		fi
		diff -y --suppress-common-lines coutput output
		if [ $? -ne 0 ]
		then
			printf "\e[1;31m: difference in output, coutput is our, output yours and the example is in example_ !\e[0m\n"
			exit 2
		fi
		if ! (( counter % 50 )) && (( counter != 0 ))
		then
			printf "\e[1;34m[$counter]\e[0m\n"
		fi
		if [ $counter != 1000 ]
		then
			if [ $our_res -ne 0 ]
			then
				printf "\e[1;33m$our_res\e[0m"
			else
				printf "\e[1;32m$our_res\e[0m"
			fi
		fi
	fi
	((counter++))
done
rm -rf gen micro_paint example_ output coutput _our_micro_paint
printf "\n\n\t\e[1;35mD\e[1;36mO\e[1;32mN\e[1;37mE\e[0m\n"
