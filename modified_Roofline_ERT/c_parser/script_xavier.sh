#!/bin/bash


while [ 1 -lt 2 ]
do

	sleep $1 
                
	#if [ $2 -eq "ram"] then
	   # `cat /sys/bus/i2c/devices/1-0041/iio_device/in_power1_input` 
	#fi

	if [ "$2" == "ram" ] 
	then
	   cat /sys/bus/i2c/devices/1-0041/iio_device/in_power1_input 
	fi

	if [ "$2" == "cpu" ] 
	then
	   cat /sys/bus/i2c/devices/1-0040/iio_device/in_power1_input
	fi

	if [ "$2" == "gpu" ] 
	then
	   cat /sys/bus/i2c/devices/1-0040/iio_device/in_power0_input
	fi

	if [ "$2" == "system" ] 
	then
	   cat /sys/bus/i2c/devices/1-0041/iio_device/in_power2_input 
	fi

	if [ "$2" == "soc" ] 
	then
	   cat /sys/bus/i2c/devices/1-0040/iio_device/in_power2_input 
	fi


	if [ "$2" == "cv" ] 
	then
	   cat /sys/bus/i2c/devices/1-0041/iio_device/in_power0_input
	fi




	if [ "$2" == "all" ] 
	then
	   ram="$( cat /sys/bus/i2c/devices/1-0041/iio_device/in_power1_input )"

	   cpu="$( cat /sys/bus/i2c/devices/1-0040/iio_device/in_power1_input )"
	
	   gpu="$( cat /sys/bus/i2c/devices/1-0040/iio_device/in_power0_input )"

	   system="$( cat /sys/bus/i2c/devices/1-0041/iio_device/in_power2_input )"
	
	   soc="$( cat /sys/bus/i2c/devices/1-0040/iio_device/in_power2_input )"
	
	   cv="$( cat /sys/bus/i2c/devices/1-0041/iio_device/in_power0_input )"

	   echo -n "RAM_Power: " $ram
	   echo -n " CPU_Power: " $cpu
	   echo -n " GPU_Power: " $gpu
	   echo -n " SOC_Power: " $soc
	   echo -n " CV_Power: " $cv
	   echo " System_Power: " $system

       fi 




done


