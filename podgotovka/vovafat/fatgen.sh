#!/bin/bash

if [[ $EUID -ne 0 ]]; then
   echo "Чтобы скрипт работал необходимо запустить его как root" 
   exit 1
fi

echo "-----------------------------------------------------------------------------------------------------------"
echo "#######    #    #######              #####  ####### #     #             #     #               ###         #"   
echo "#         # #      #                #     # #       ##    #             #     #              #   #       ##"   
echo "#        #   #     #                #       #       # #   #             #     #             #     #     # #"   
echo "#####   #     #    #                #  #### #####   #  #  #             #     #             #     #       #"   
echo "#       #######    #                #     # #       #   # #              #   #              #     # ###   #"   
echo "#       #     #    #                #     # #       #    ##               # #                #   #  ###   #"   
echo "#       #     #    #                 #####  ####### #     #                #                  ###   ### #####" 
echo "------------------------------------------------------------------------------------------------------------"

echo "Начинаем генерацию жирного диска fat12, ждите :))"

sleep 10

a=$(( $RANDOM % 2 ))
a=$((a+1))
mkfs.fat fatdisk.img -s $a -C 1440
mkdir tmpmount
mount fatdisk.img tmpmount
r=$(( $RANDOM % 10 ))
i=0
for ((i=0; i <= r; i++))
	do
		dd if=/dev/urandom of=tmpmount/RANDOM$i.bin bs=1 count=2048
		
	done
i=0
for ((i=0; i <= r; i++))
	do
		rm tmpmount/RANDOM$i.bin
		
	done
i=0
for ((i=0; i <= r; i++))
	do
		dd if=/dev/urandom of=tmpmount/RANDOM$i.bin bs=1 count=2048
		
	done
dd if=/dev/urandom of=tmpmount/TARGET.bin bs=1 count=2048
dd if=/dev/urandom of=tmpmount/RANDOM10.bin bs=1 count=2048
dd if=/dev/urandom of=tmpmount/RANDOM11.bin bs=1 count=2048

clear
echo "Почти готово..."
sleep 5
clear

echo "Значение md5 для проверки:"
md5sum tmpmount/TARGET.bin
echo "Название образа - fatdisk.img"

umount tmpmount
rm -d tmpmount
echo "Образ создан успешно, не забудьте его удалить перед созданием нового"


