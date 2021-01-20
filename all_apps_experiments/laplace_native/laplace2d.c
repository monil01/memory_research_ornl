/*
 *  Copyright 2012 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <math.h>
#include <string.h>
#include "timer.h"
#include <stdio.h>
#ifdef _OPENACCM
#include <openacc.h>
#endif


#include "papi.h" /* This needs to be included every time you use PAPI */

#define NUM_EVENTS 8
#define ERROR_RETURN(retval) { fprintf(stderr, "Error %d %s:line %d: \n", retval,__FILE__,__LINE__);  exit(retval); }


#ifndef VERIFICATION
#define VERIFICATION 1
#endif

#ifndef NN
//#define NN 8192
#define NN 4096
//#define NN 1024
#endif 

#ifdef _OPENARC_

#if NN == 1024
#pragma openarc #define NN 1024
#elif NN == 2048
#pragma openarc #define NN 2048
#elif NN == 3072
#pragma openarc #define NN 3072
#elif NN == 3072
#pragma openarc #define NN 3072
#elif NN == 4096
#pragma openarc #define NN 4096
#endif

#endif

#if VERIFICATION == 1
double A_CPU[NN][NN];
double Anew_CPU[NN][NN];
#endif


double laplace2d_stencil(double (*A_CPU)[NN], double (*Anew_CPU)[NN], double error)
{
int i, j;
	#pragma omp parallel for private(j, i)
                for( j = 1; j < NN-1; j++)
                {
		double lerror = 0.0;
                    for( i = 1; i < NN-1; i++ )
                    {
                        Anew_CPU[j][i] = 0.25 * ( A_CPU[j][i+1] + A_CPU[j][i-1]
                                                  + A_CPU[j-1][i] + A_CPU[j+1][i]);
                        lerror = fmax( lerror, fabs(Anew_CPU[j][i] - A_CPU[j][i]));
                    }
					#pragma omp critical
					error = fmax(error,lerror);
                }
	
return error;
}

int main(int argc, char** argv)
{

    int EventSet = PAPI_NULL;

    int tmp;
    /*must be initialized to PAPI_NULL before calling PAPI_create_event*/

    long long values[NUM_EVENTS];
    /*This is where we store the values we read from the eventset */

    /* We use number to keep track of the number of events in the EventSet */
    int retval, number, native;

    char errstring[PAPI_MAX_STR_LEN];

    /*************************************************************************** 
 *     *  This part initializes the library and compares the version number of the*
 *         * header file, to the version of the library, if these don't match then it *
 *             * is likely that PAPI won't work correctly.If there is an error, retval    *
 *                 * keeps track of the version number.                                       *
 *                     ***************************************************************************/


    if((retval = PAPI_library_init(PAPI_VER_CURRENT)) != PAPI_VER_CURRENT )
       ERROR_RETURN(retval);


    /* Creating the eventset */
    if ( (retval = PAPI_create_eventset(&EventSet)) != PAPI_OK)
       ERROR_RETURN(retval);

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

int i = 0;
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


    /* get the number of events in the event set */
    number = 0;
    if ( (retval = PAPI_list_events(EventSet, NULL, &number)) != PAPI_OK)
       ERROR_RETURN(retval);

    //printf("There are %d events in the event set\n", number);

    /* Start counting */






    int n = NN;
    int m = n;
    int iter_max = 1;

    double tol = 1.0e-6;
    double error     = 1.0;
    int j;
i= 0;
    int iter = 0;
    double runtime;

	double (*A)[NN] = (double (*)[NN])malloc(sizeof(double)*n*n);
	double (*Anew)[NN] = (double (*)[NN])malloc(sizeof(double)*n*n);
    memset(A, 0, n * m * sizeof(double));
    //memset(Anew, 0, n * m * sizeof(double));

#if VERIFICATION == 1
    memset(A_CPU, 0, n * m * sizeof(double));
    //memset(Anew_CPU, 0, n * m * sizeof(double));
#endif

    for (j = 0; j < n; j++)
    {
        A[j][0]    = 1.0;
        //Anew[j][0] = 1.0;

#if VERIFICATION == 1
        A_CPU[j][0] = 1.0;
        //Anew_CPU[j][0] = 1.0;
#endif
    }

    printf("Jacobi relaxation Calculation: %d x %d mesh\n", n, m);

    StartTimer();
	printf("iter: %d\n", iter);

    runtime = GetTimer();
    printf("Accelerator Elapsed time %f s\n", runtime / 1000);

#if VERIFICATION == 1
    {
    	StartTimer();
        error = 1.0;
        iter = 0;
        while ( error > tol && iter < iter_max )
        {
            error = 0.0;

            {

	    if ( (retval = PAPI_start(EventSet)) != PAPI_OK)
       			ERROR_RETURN(retval);



		error = laplace2d_stencil(A_CPU, Anew_CPU, error);

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

    printf("stride %lld %lld \n", read, write);



            }

			#pragma omp parallel for private(j, i)
            for( j = 1; j < n-1; j++)
            {
                for( i = 1; i < m-1; i++ )
                {
                    A_CPU[j][i] = Anew_CPU[j][i];
                }
            }
            if(iter % 100 == 0) printf("%5d, %0.6f\n", iter, error);
            iter++;
        }
    	runtime = GetTimer();
    	printf("CPU Elapsed time %f s\n", runtime / 1000);

        {
            double cpu_sum = 0.0f;
            double gpu_sum = 0.0f;
            double rel_err = 0.0f;

            for (i = 1; i < m-1; i++)
            {
                cpu_sum += A_CPU[i][i]*A_CPU[i][i];
                gpu_sum += A[i][i]*A[i][i];
            }

            cpu_sum = sqrt(cpu_sum);
            gpu_sum = sqrt(gpu_sum);
            rel_err = (cpu_sum-gpu_sum)/cpu_sum;

            if(rel_err < 1e-6)
            {
                printf("Verification Successful err = %e\n", rel_err);
            }
            else
            {
                printf("Verification Fail err = %e\n", rel_err);
            }
        }
    }
#endif

}
