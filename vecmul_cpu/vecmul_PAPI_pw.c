/*****************************************************************************
* This example shows how to use PAPI_add_event, PAPI_start, PAPI_read,       *
*  PAPI_stop and PAPI_remove_event.                                          *
******************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#include "papi.h" /* This needs to be included every time you use PAPI */

#define NUM_EVENTS 2
#define ERROR_RETURN(retval) { fprintf(stderr, "Error %d %s:line %d: \n", retval,__FILE__,__LINE__);  exit(retval); }

void vecMul(float *a, float *b, float *c, int n)
{
    for(int i = 0; i < n; i++)
    {
        c[i] = a[i] * b[i];
        //std::cout << c[i] << "\n";
    }
}


int main()
{
    // Size of vectors
    int n = 100000000;

    // Host input vectors
    float *h_a;
    float *h_b;
    //Host output vector
    float *h_c;

    // Device input vectors
    float *d_a;
    float *d_b;
    //Device output vector
    float *d_c;

    // Size, in bytes, of each vector
    size_t bytes = n*sizeof(float);

    // Allocate memory for each vector on host
    h_a = (float*)malloc(bytes);
    h_b = (float*)malloc(bytes);
    h_c = (float*)malloc(bytes);
 
    //int i;
    // Initialize vectors on host
    for( int i = 0; i < n; i++ ) {
        h_a[i] = sin(i)*sin(i);
        h_b[i] = cos(i)*cos(i);
    }



    int EventSet = PAPI_NULL;
   
    int tmp, i;
    /*must be initialized to PAPI_NULL before calling PAPI_create_event*/
    
    long long values[NUM_EVENTS];
    /*This is where we store the values we read from the eventset */
    
    /* We use number to keep track of the number of events in the EventSet */ 
    int retval, number;
   
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

    //printf("Cache Misses %lld \n", values[0] );
    if ( (retval = PAPI_add_event(EventSet, PAPI_L3_DCM)) != PAPI_OK)
      ERROR_RETURN(retval);

    //printf("load misses %lld \n", values[1] );
    if ( (retval = PAPI_add_event(EventSet, PAPI_L3_LDM)) != PAPI_OK)
    //if ( (retval = PAPI_add_event(EventSet, PAPI_L3_LDM)) != PAPI_OK)
      ERROR_RETURN(retval);
/*
    //printf("data cache access %lld \n", values[3] );
    if ( (retval = PAPI_add_event(EventSet, PAPI_TOT_INS)) != PAPI_OK)
    //if ( (retval = PAPI_add_event(EventSet, PAPI_L3_DCA)) != PAPI_OK)
      ERROR_RETURN(retval);

    //printf("data cache reads %lld \n", values[4] );
    if ( (retval = PAPI_add_event(EventSet, PAPI_TOT_CYC)) != PAPI_OK)
    //if ( (retval = PAPI_add_event(EventSet, PAPI_L3_DCR)) != PAPI_OK)
      ERROR_RETURN(retval);

    //printf("data cache writes %lld \n", values[5] );
    if ( (retval = PAPI_add_event(EventSet, PAPI_L3_DCW)) != PAPI_OK)
      ERROR_RETURN(retval);

    //printf("instruction cache accesses %lld \n", values[6] );
    if ( (retval = PAPI_add_event(EventSet, PAPI_L3_ICA)) != PAPI_OK)
      ERROR_RETURN(retval);

    //printf("instruction cache reads %lld \n", values[7] );
    if ( (retval = PAPI_add_event(EventSet, PAPI_L3_ICR)) != PAPI_OK)
      ERROR_RETURN(retval);


    //printf("total cache accesses %lld \n", values[8] );
    if ( (retval = PAPI_add_event(EventSet, PAPI_L3_TCA)) != PAPI_OK)
      ERROR_RETURN(retval);


    //printf("total cache reads %lld \n", values[9] );
    if ( (retval = PAPI_add_event(EventSet, PAPI_L3_TCR)) != PAPI_OK)
      ERROR_RETURN(retval);


    printf("total cache writes %lld \n", values[10] );
    if ( (retval = PAPI_add_event(EventSet, PAPI_L3_TCW)) != PAPI_OK)
      ERROR_RETURN(retval);

*/


    /* get the number of events in the event set */
    number = 0;
    if ( (retval = PAPI_list_events(EventSet, NULL, &number)) != PAPI_OK)
       ERROR_RETURN(retval);

    printf("There are %d events in the event set\n", number);

    /* Start counting */


    if ( (retval = PAPI_start(EventSet)) != PAPI_OK)
       ERROR_RETURN(retval);
   
    //vecMul(h_a, h_b, h_c, n);
    
    /* you can replace your code here */
    /*tmp=0;
    for (i = 0; i < 2000000; i++)
    {
       tmp = i + tmp;
    }*/

  
    /* read the counter values and store them in the values array */
    //if ( (retval=PAPI_read(EventSet, values)) != PAPI_OK)
    //   ERROR_RETURN(retval);

    //printf("The total instructions executed for the first loop are %lld \n", values[0] );
    //printf("The total cycles executed for the first loop are %lld \n",values[1]);
  
    /* our slow code again */

    vecMul(h_a, h_b, h_c, n);

    /* tmp=0;
    for (i = 0; i < 2000000; i++)
    {
       tmp = i + tmp;
    } */

    /* Stop counting and store the values into the array */
    if ( (retval = PAPI_stop(EventSet, values)) != PAPI_OK)
       ERROR_RETURN(retval);

    printf("DCM Cache Misses %lld \n", values[0] );
    printf("ICM load misses %lld \n", values[1] );

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


