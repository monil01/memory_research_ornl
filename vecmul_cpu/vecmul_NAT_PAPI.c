/*****************************************************************************
* This example shows how to use PAPI_add_event, PAPI_start, PAPI_read,       *
*  PAPI_stop and PAPI_remove_event.                                          *
******************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
//#include <iostream.h>
#include <math.h>
#include <time.h>

#include "papi.h" /* This needs to be included every time you use PAPI */

#define NUM_EVENTS 8
#define ERROR_RETURN(retval) { fprintf(stderr, "Error %d %s:line %d: \n", retval,__FILE__,__LINE__);  exit(retval); }

#ifndef STRIDE
#define STRIDE 1
int stride = STRIDE;
#else
//int stride = 1;
int stride = STRIDE;

#endif

double getTime() {
    double time;
    struct timeval tm;
    gettimeofday(&tm, NULL);
    time = tm.tv_sec + (tm.tv_usec / 1000000.0);
    return time;
} 


void vecMul(float *a, float *b, float *c, int n)
{
    float total;
    int i = 0;
    //srand(time(NULL));   // Initialization, should only be called once.
#ifdef STRIDE
    for(i = 0; i < n; i= i + STRIDE)
#else
    for(i = 0; i < n; i= i + 1)
#endif
    //for(i = 0; i < n; i= i + stride)
    {
        c[i] = a[i] * b[i];
	//int r = rand()*rand()*rand()*rand();      // Returns a pseudo-random integer between 0 and RAND_MAX.
	
        //printf("%d\n", i);
	//break;
    }
}

void fill_cache(float *a, int n)
{
    float delta = 1.9;
    int i = 0;
    for(i = 0; i < n; i++)
    {
        a[i] = a[i] * delta;
        //std::cout << c[i] << "\n";
    }
}

int main(int argc, char** argv)
{
    // Size of vectors
    int n = 100000000;
    int fill = 10000000;
    int i = 0;


    if (argc>1) {
	stride = atoi(argv[1]);
    }
    if (argc>2) {
	n = atoi(argv[2]);
    }

    //printf("stride %d, n %d\n", stride, n);


    // Host input vectors
    float *h_a;
    float *h_b;
    //Host output vector
    float *h_c;
    float *h_d;


    // Size, in bytes, of each vector
    size_t bytes = n*sizeof(float);
    size_t fill_bytes = fill*sizeof(float);

    // Allocate memory for each vector on host
    h_a = (float*)malloc(bytes);
    h_b = (float*)malloc(bytes);
    h_c = (float*)malloc(bytes);

    h_d = (float*)malloc(fill_bytes);


 
    //int i;
    // Initialize vectors on host
    for( i = 0; i < n; i++ ) {
        h_a[i] = 9.5;
        //h_a[i] = sin(i)*sin(i);
        h_b[i] = 3;
        h_c[i] = 3;
        //h_b[i] = cos(i)*cos(i);
    }


    // Initialize vectors on host
    for( i = 0; i < fill; i++ ) {
        h_d[i] = 20;
        //h_d[i] = sin(i)*sin(i);
    }

    fill_cache(h_d, fill);


    int EventSet = PAPI_NULL;
   
    int tmp;
    /*must be initialized to PAPI_NULL before calling PAPI_create_event*/
    
    long long values[NUM_EVENTS];
    /*This is where we store the values we read from the eventset */
    
    /* We use number to keep track of the number of events in the EventSet */ 
    int retval, number, native;
   
    char errstring[PAPI_MAX_STR_LEN];
  
    /*************************************************************************** 
    *  This part initializes the library and compares the version number of the*
    * header file, to the version of the library, if these don't match then it *
    * is likely that PAPI won't work correctly.If there is an error, retval    *
    * keeps track of the version number.                                       *
    ***************************************************************************/


    if((retval = PAPI_library_init(PAPI_VER_CURRENT)) != PAPI_VER_CURRENT )
       ERROR_RETURN(retval);
     
     
    /* Creating the eventset */              
    if ( (retval = PAPI_create_eventset(&EventSet)) != PAPI_OK)
       ERROR_RETURN(retval);

   /* static char *native_name[] =
         { "OFFCORE_RESPONSE_1:L3_MISS", 
          "OFFCORE_RESPONSE_1:L3_MISS_LOCAL", 
          "OFFCORE_RESPONSE_0:L3_MISS", 
          "OFFCORE_RESPONSE_0:L3_MISS_LOCAL", 
            NULL };*/
 /* char *native_name[] =
         { "ix86arch::LLC_MISSES:t=0", 
          "ix86arch::LLC_MISSES:e=0", 
            NULL }; */


 char *native_name[] =
	{"bdx_unc_imc0::UNC_M_CAS_COUNT:RD:cpu=21",
	"bdx_unc_imc1::UNC_M_CAS_COUNT:RD:cpu=21",
	"bdx_unc_imc4::UNC_M_CAS_COUNT:RD:cpu=21",
	"bdx_unc_imc5::UNC_M_CAS_COUNT:RD:cpu=21",
	"bdx_unc_imc0::UNC_M_CAS_COUNT:WR:cpu=21",
	"bdx_unc_imc1::UNC_M_CAS_COUNT:WR:cpu=21",
	"bdx_unc_imc4::UNC_M_CAS_COUNT:WR:cpu=21",
	"bdx_unc_imc5::UNC_M_CAS_COUNT:WR:cpu=21",
         NULL }; 

/*
 char *native_name[] =
         { "OFFCORE_RESPONSE_0:ANY_DATA", 
          "OFFCORE_RESPONSE_0:L3_MISS", 
          "OFFCORE_RESPONSE_1:ANY_DATA", 
          "OFFCORE_RESPONSE_1:L3_MISS", 
            NULL }; 
*/

          /*"perf::LLC-STORE-MISSES:excl=0", 
          "perf::LLC-STORE-MISSES:precise=0", */


    for ( i = 0; native_name[i] != NULL; i++ ) {
        retval = PAPI_event_name_to_code( native_name[i], &native );
        //printf(" code name: %d \n", native);
        if ( retval != PAPI_OK )
      	    ERROR_RETURN(retval);
            //test_fail( __FILE__, __LINE__, "PAPI_event_name_to_code", retval );
        printf( "Adding %s\n", native_name[i] );
        if ( ( retval = PAPI_add_event( EventSet, native ) ) != PAPI_OK )
            ERROR_RETURN(retval);
            //test_fail( __FILE__, __LINE__, "PAPI_add_event", retval );
    }


    //printf("Cache Misses %lld \n", values[0] );
    //if ( (retval = PAPI_add_event(EventSet, PAPI_L3_TCM)) != PAPI_OK)
      //ERROR_RETURN(retval);

    //printf("load misses %lld \n", values[1] );
    //if ( (retval = PAPI_add_event(EventSet, PAPI_L3_TCA)) != PAPI_OK)
    //if ( (retval = PAPI_add_event(EventSet, PAPI_L3_LDM)) != PAPI_OK)
      //ERROR_RETURN(retval);


    /* get the number of events in the event set */
    number = 0;
    if ( (retval = PAPI_list_events(EventSet, NULL, &number)) != PAPI_OK)
       ERROR_RETURN(retval);

    //printf("There are %d events in the event set\n", number);

    /* Start counting */


    if ( (retval = PAPI_start(EventSet)) != PAPI_OK)
       ERROR_RETURN(retval);
 

    double seconds = 0;
    double startTime, endTime;
    startTime = getTime();

    vecMul(h_a, h_b, h_c, n);

    endTime = getTime();
    seconds += (double)(endTime - startTime);
    printf("Total time: %15.6lf \n", seconds);



    /* Stop counting and store the values into the array */
    if ( (retval = PAPI_stop(EventSet, values)) != PAPI_OK)
       ERROR_RETURN(retval);

    long long read = 0, write = 0;
    printf("IMC0 load misses %lld \n", values[0] );
    printf("IMC1 load misses %lld \n", values[1] );
    printf("IMC4 load misses %lld \n", values[2] );
    printf("IMC5 load misses %lld \n", values[3] );
    printf("IMC0 store misses %lld \n", values[4] );
    printf("IMC1 store misses %lld \n", values[5] );
    printf("IMC4 store misses %lld \n", values[6] );
    printf("IMC5 store misses %lld \n", values[7] );

    read =  values[0] +values[1] +values[2] +values[3];
    write =  values[4] +values[5] +values[6] +values[7];

    printf("stride %d %lld %lld \n", stride, read, write);

/*
    printf("DCA data cache access %lld \n", values[3] );
    printf("DCR data cache reads %lld \n", values[4] );
    printf("DCW data cache writes %lld \n", values[5] );
    printf("ICA instruction cache accesses %lld \n", values[6] );
    printf("ICR instruction cache reads %lld \n", values[7] );
    printf("TCA total cache accesses %lld \n", values[8] );
    printf("TCR total cache reads %lld \n", values[9] );
    printf("TCW total cache writes %lld \n", values[10] );
*/
    /* Remove event: We are going to take the PAPI_TOT_INS from the eventset */
    //if( (retval = PAPI_remove_event(EventSet, PAPI_TOT_INS)) != PAPI_OK)
    //   ERROR_RETURN(retval);
    //printf("Removing PAPI_TOT_INS from the eventset\n"); 

    /* Now we list how many events are left on the event set */
    //number = 0;
    //if ((retval=PAPI_list_events(EventSet, NULL, &number))!= PAPI_OK)
    //  ERROR_RETURN(retval);

    //printf("There is only %d event left in the eventset now\n", number);

    /* free the resources used by PAPI */
    PAPI_shutdown();

    // Release host memory
    free(h_a);
    free(h_b);
    free(h_c);
 
    exit(0);
}


