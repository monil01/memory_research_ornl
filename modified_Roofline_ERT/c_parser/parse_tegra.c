#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>

//include header/generate_statistics.h

int get_current_power_RAM();
int get_current_power_GPU();
int get_current_power_CPU();
int get_current_power_SOC();
int get_current_power_CV();
int get_current_power_SYSTEM();

void while_loop(char * option, int period, int *p_cpu,
		int lock, int colocate){

   int temp;
printf(" %d %d %d\n", lock, colocate, *p_cpu);
   while(1) {
 
       if (lock == 1){
           if(colocate == 0) {
       	        if (*p_cpu == 33){
			break;
		}
		else if (*p_cpu == 0){
		   //usleep(period*1000);
		   continue;
		}
	   }
	   else if(colocate == 1) {
		if (*p_cpu >= 3) break;
	   }
        }

	if (strcmp(option, "ram") == 0){

            temp = get_current_power_RAM();
	    printf("%d\n",temp);
	}

	if (strcmp(option, "cpu") == 0){

            temp = get_current_power_CPU();
	    printf("%d\n",temp);
	}

	if (strcmp(option, "gpu") == 0){

            temp = get_current_power_GPU();
	    printf("%d\n",temp);
	}

	if (strcmp(option, "soc") == 0){

            temp = get_current_power_SOC();
	    printf("%d\n",temp);
	}

	if (strcmp(option, "cv") == 0){

            temp = get_current_power_CV();
	    printf("%d\n",temp);
	}

	if (strcmp(option, "system") == 0){

            temp = get_current_power_SYSTEM();
	    printf("%d\n",temp);
	}
	usleep(period*1000);
   }

}

int main( int argc, char ** argv){

     int period, iterations, colocate, lock = 0;
     period = 1000;
     iterations = 100;
     colocate = 0;
     char * print_option;
     print_option = "ram";
 
     //sleep(2);
     key_t shmkey;                 /*      shared memory key       */
     int shmid;                    /*      shared memory id        */

     int *p_cpu;                       /*      shared variable         *//*shared */
    /* initialize a shared variable in shared memory */
     shmkey = ftok ("/dev/null", 5);       /* valid directory name and a number */
     //printf ("shmkey for p = %d\n", shmkey);
     shmid = shmget (shmkey, sizeof (int), 0644 | IPC_CREAT);
     if (shmid < 0){                           /* shared memory error check */
        perror ("shmget\n");
        exit (1);
     }
     //pthread_mutex_t *m;
     //Mutex a(m,false);
     p_cpu = (int *) shmat (shmid, NULL, 0);   /* attach p to shared memory */
     *p_cpu = 0;
     //printf ("p=%d is allocated in shared memory.\n\n", *p);



     if (argc == 1) {
        printf ("Default interval selected as 1000 msec and print ption ram \n");
	// setting default time
	period = 1000;
	print_option = "ram";
     }
     for ( int i = 1; i < argc; i++){

	 if ( strcmp(argv[i], "-t") == 0) {
	     period = strtoul(argv[i+1], NULL, 0);	
             //printf("Period was set to %d \n", period);
	     i++;
         }

	 else if ( strcmp(argv[i], "-p") == 0) {
	    print_option = argv[i+1];	
            //printf("Print options is set to %s \n", print_option);
	    i++;
         }
	
	 else if ( strcmp(argv[i], "-c") == 0) {
	    colocate = strtoul(argv[i+1], NULL, 0);	
            //printf("Print options is set to %s \n", print_option);
	    i++;
         }

	 else if ( strcmp(argv[i], "-l") == 0) {
	    lock = strtoul(argv[i+1], NULL, 0);	
            //printf("Print options is set to %s \n", print_option);
	    i++;
         }



         else {
            printf ("Unknown argument\n");
              return 1;
	 }
     }

     int size = period/iterations;
  
     if (lock == 1){
           if(colocate == 0) {
		for(;;) {
			if (*p_cpu == 1) break;
		}
	   }
	   else if(colocate == 1) {
		for(;;) {
			if (*p_cpu == 2) break;
		}
	   }
     }

     while_loop(print_option, period, p_cpu, lock, colocate);

     shmdt (p_cpu);
     shmctl (shmid, IPC_RMID, 0);

return 0;
}

    int get_current_power_RAM(){
	int ram_power = 0;
        FILE *f = fopen("/sys/bus/i2c/devices/1-0041/iio_device/in_power1_input"
			, "r");
	if(f) {

            if (fscanf(f, "%d", &ram_power)) {}
	    //printf("%d",gpu_power);
	    fclose(f);

	} else 
            printf("failed to open /sys/bus/i2c/devices/1-0040/iio_device/in_power1_input");

	return ram_power;

    } 

    

    int get_current_power_CPU(){
	int cpu_power = 0;
        FILE *f = fopen("/sys/bus/i2c/devices/1-0040/iio_device/in_power1_input"
			, "r");
	if(f) {

            if (fscanf(f, "%d", &cpu_power)) {}
	    //printf("%d",gpu_power);
	    fclose(f);

	} else 
            printf("failed to open /sys/bus/i2c/devices/1-0040/iio_device/in_power1_input");

	return cpu_power;

    }

    int get_current_power_GPU(){
	int gpu_power = 0;
        FILE *f = fopen("/sys/bus/i2c/devices/1-0040/iio_device/in_power0_input"
			, "r");
	if(f) {

            if (fscanf(f, "%d", &gpu_power)) {}
	    //printf("%d",gpu_power);
	    fclose(f);

	} else 
            printf("failed to open /sys/bus/i2c/devices/1-0040/iio_device/in_power0_input");

	return gpu_power;

    }

    int get_current_power_SYSTEM(){
	int system_power = 0;
        FILE *f = fopen("/sys/bus/i2c/devices/1-0041/iio_device/in_power2_input"
			, "r");
	if(f) {

            if (fscanf(f, "%d", &system_power)) {}
	    //printf("%d",gpu_power);
	    fclose(f);

	} else 
            printf("failed to open /sys/bus/i2c/devices/1-0041/iio_device/in_power2_input");

	return system_power;


    }

    int get_current_power_SOC(){
	int soc_power = 0;
        FILE *f = fopen("/sys/bus/i2c/devices/1-0040/iio_device/in_power2_input"
			, "r");
	if(f) {

            if (fscanf(f, "%d", &soc_power)) {}
	    //printf("%d",gpu_power);
	    fclose(f);

	} else 
            printf("failed to open /sys/bus/i2c/devices/1-0040/iio_device/in_power2_input");

	return soc_power;


    }


    int get_current_power_CV(){
	int cv_power = 0;
        FILE *f = fopen("/sys/bus/i2c/devices/1-0041/iio_device/in_power0_input"
			, "r");
	if(f) {

            if (fscanf(f, "%d", &cv_power)) {}
	    //printf("%d",gpu_power);
	    fclose(f);

	} else 
            printf("failed to open /sys/bus/i2c/devices/1-0041/iio_device/in_power0_input \n");

	return cv_power;

    }


