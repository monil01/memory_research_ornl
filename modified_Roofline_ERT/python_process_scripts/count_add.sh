#!/bin/bash


bw_power(){

   #echo "File: $1 ---------------"
   #echo -n "${1}_"

   line=`cat $1 | wc -l`
   
#while IFS= read -r line; do
    #echo $line
#done < "$1"

declare -i x=0
declare -i bw=0
declare -i flops=0
declare -i bytes=0
declare -i bytes=0

while IFS=':' read -ra ADDR; do
      x=0
      for i in "${ADDR[@]}"; do
         #echo " asdfas" 
	 if [ "$x" == "1" ]; then
         echo -n "$i" 
	 fi
	 x+=1
      done
      echo -n " " 
 done < "$1"

   #energy=$sum*50/1000
   #avg_power=$sum/$count

   #echo -n "${sum}_"
   #echo -n "${zero_num}_"
   #echo "${avg_power}"
   #echo "Total power consumption: $energy KW-Hour"
}


declare -i zero_power=0


if [ "$1" = "gpu" ]; then

    #zero_power=468
    zero_power=0

    for d in data/standalone_gpu/$1_20*; do
       bw_power  $d $zero_power
    done

fi


bww_power(){

   #echo "File: $1 ---------------"
   #echo -n "${1}_"

   line=`cat $1 | wc -l`
   

   #echo "Total number of 10ms iterations: $line"
   declare -i sum=0
   declare -i zero_num=0
   declare -i energy=0
   declare -i avg_power=0
   declare -i count=0
   while IFS='' read -r line || [[ -n "$line" ]]; do
      #echo "Text read from file: $line"
      sum=$sum+$line-$2
      count=$count+1
      if [ "$line" = "0" ]; then
          zero_num=$zero_num+1
      fi
   done < "$1"

   energy=$sum*50/1000
   avg_power=$sum/$count

   echo -n "${sum}_"
   echo -n "${zero_num}_"
   echo "${avg_power}"
   #echo "Total power consumption: $energy KW-Hour"
}

