#include <inttypes.h>
#include <iostream>
#include <omp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <sys/shm.h>
#include <unistd.h>

#define ERT_FLOP 2
#define ERT_TRIALS_MIN 1
#define ERT_WORKING_SET_MIN 1
#define GBUNIT (1024 * 1024 * 1024)

#define REP2(S)                                                                \
    S;                                                                         \
    S
#define REP4(S)                                                                \
    REP2(S);                                                                   \
    REP2(S)
#define REP8(S)                                                                \
    REP4(S);                                                                   \
    REP4(S)
#define REP16(S)                                                               \
    REP8(S);                                                                   \
    REP8(S)
#define REP32(S)                                                               \
    REP16(S);                                                                  \
    REP16(S)
#define REP64(S)                                                               \
    REP32(S);                                                                  \
    REP32(S)
#define REP128(S)                                                              \
    REP64(S);                                                                  \
    REP64(S)
#define REP256(S)                                                              \
    REP128(S);                                                                 \
    REP128(S)
#define REP512(S)                                                              \
    REP256(S);                                                                 \
    REP256(S)

#define KERNEL1(a,b,c)   ((a) = (b) + (c))
#define KERNEL2(a, b, c) ((a) = (a) * (b) + (c))

#ifdef BW_PCT

#if BW_PCT == 100
int flop = 4;
#endif
#if BW_PCT == 90
int flop = 18;
#endif

#if BW_PCT == 80
int flop = 22;
#endif

#if BW_PCT == 70
int flop = 26;
#endif

#if BW_PCT == 60
int flop = 32;

#endif

#if BW_PCT == 50
int flop = 38;

#endif

#if BW_PCT == 40
int flop = 46;
#endif

#if BW_PCT == 30
int flop = 62;
#endif

#if BW_PCT == 20
int flop = 104;
#endif

#if BW_PCT == 10
int flop = 148;
#endif

#endif

#ifdef INTENS

#if INTENS == 1
int flop = 1;
#endif
#if INTENS == 2
int flop = 2;
#endif

#if INTENS == 3
int flop = 4;
#endif

#if INTENS == 4
int flop = 6;
#endif

#if INTENS == 5
int flop = 8;

#endif

#if INTENS == 6
int flop = 12;

#endif

#if INTENS == 7 
int flop = 16;
#endif

#if INTENS == 8
int flop = 20;
#endif

#if INTENS == 9
int flop = 28;
#endif

#if INTENS == 10
int flop = 32;
#endif

#if INTENS == 11
int flop = 48;
#endif

#if INTENS == 12
int flop = 64;
#endif

#if INTENS == 13
int flop = 96;
#endif

#if INTENS == 14
int flop = 128;
#endif

#if INTENS == 15
int flop = 192;

#endif

#if INTENS == 16
int flop = 256;

#endif

#if INTENS == 17 
int flop = 384;
#endif

#if INTENS == 18
int flop = 512;
#endif

#if INTENS == 19
int flop = 768;
#endif

#if INTENS == 20
int flop = 1024;
#endif

#endif



void initialize(uint64_t nsize, double *__restrict__ A, double value) {
    uint64_t i;
    for (i = 0; i < nsize; ++i) {
        A[i] = value;
    }
}

void kernel8(uint64_t nsize, uint64_t ntrials, double *__restrict__ A,
            int *bytes_per_elem, int *mem_accesses_per_elem) {
    *bytes_per_elem = sizeof(*A);
    *mem_accesses_per_elem = 2;

    double alpha = 0.5;
    uint64_t i, j;
    for (j = 0; j < ntrials; ++j) {
#pragma unroll(8)
        for (i = 0; i < nsize; ++i) {
            double beta = 0.8;

            //int flop = 20;

//#if (ERT_FLOP & 4) == 4       /* add 4 flops */
      REP2(KERNEL2(beta,A[i],alpha));

//#if (ERT_FLOP & 16) == 16     /* add 16 flops */
      REP8(KERNEL2(beta,A[i],alpha));


            A[i] = beta;
        }
        alpha = alpha * (1 - 1e-8);
    }
}


void kernel6(uint64_t nsize, uint64_t ntrials, double *__restrict__ A,
            int *bytes_per_elem, int *mem_accesses_per_elem) {
    *bytes_per_elem = sizeof(*A);
    *mem_accesses_per_elem = 2;

    double alpha = 0.5;
    uint64_t i, j;
    for (j = 0; j < ntrials; ++j) {
#pragma unroll(8)
        for (i = 0; i < nsize; ++i) {
            double beta = 0.8;

//#if (ERT_FLOP & 4) == 4       /* add 4 flops */
      REP2(KERNEL2(beta,A[i],alpha));
//#if (ERT_FLOP & 8) == 8       /* add 8 flops */
      REP4(KERNEL2(beta,A[i],alpha));

            A[i] = beta;
        }
        alpha = alpha * (1 - 1e-8);
    }
}

void kernel11(uint64_t nsize, uint64_t ntrials, double *__restrict__ A,
            int *bytes_per_elem, int *mem_accesses_per_elem) {
    *bytes_per_elem = sizeof(*A);
    *mem_accesses_per_elem = 2;

    double alpha = 0.5;
    uint64_t i, j;
    for (j = 0; j < ntrials; ++j) {
#pragma unroll(8)
        for (i = 0; i < nsize; ++i) {
            double beta = 0.8;

//int flop = 48;
//#if (ERT_FLOP & 16) == 16     /* add 16 flops */
      REP8(KERNEL2(beta,A[i],alpha));
//#if (ERT_FLOP & 32) == 32     /* add 32 flops */
      REP16(KERNEL2(beta,A[i],alpha));
            //      REP128(KERNEL2(beta,A[i],alpha));
            // if ((ERT_FLOP & 512) == 512)   /* add 512 flops */
            //      REP256(KERNEL2(beta,A[i],alpha));
            // if ((ERT_FLOP & 1024) == 1024) /* add 1024 flops */
            //     REP512(KERNEL2(beta,A[i],alpha));
            A[i] = beta;
        }
        alpha = alpha * (1 - 1e-8);
    }
}

void kernel11(uint64_t nsize, uint64_t ntrials, double *__restrict__ A,
            int *bytes_per_elem, int *mem_accesses_per_elem) {
    *bytes_per_elem = sizeof(*A);
    *mem_accesses_per_elem = 2;

    double alpha = 0.5;
    uint64_t i, j;
    for (j = 0; j < ntrials; ++j) {
#pragma unroll(8)
        for (i = 0; i < nsize; ++i) {
            double beta = 0.8;

//int flop = 48;
//#if (ERT_FLOP & 16) == 16     /* add 16 flops */
      REP8(KERNEL2(beta,A[i],alpha));
//#if (ERT_FLOP & 32) == 32     /* add 32 flops */
      REP16(KERNEL2(beta,A[i],alpha));
            //      REP128(KERNEL2(beta,A[i],alpha));
            // if ((ERT_FLOP & 512) == 512)   /* add 512 flops */
            //      REP256(KERNEL2(beta,A[i],alpha));
            // if ((ERT_FLOP & 1024) == 1024) /* add 1024 flops */
            //     REP512(KERNEL2(beta,A[i],alpha));
            A[i] = beta;
        }
        alpha = alpha * (1 - 1e-8);
    }
}

void kernel(uint64_t nsize, uint64_t ntrials, double *__restrict__ A,
            int *bytes_per_elem, int *mem_accesses_per_elem) {
    *bytes_per_elem = sizeof(*A);
    *mem_accesses_per_elem = 2;

    double alpha = 0.5;
    uint64_t i, j;
    for (j = 0; j < ntrials; ++j) {
#pragma unroll(8)
        for (i = 0; i < nsize; ++i) {
            double beta = 0.8;

#ifdef BW_PCT
#if BW_PCT == 100
            // if ((ERT_FLOP & 4) == 4)       /* add 4 flops */
            REP2(KERNEL2(beta, A[i], alpha));

#endif
#if BW_PCT == 90
            // if ((ERT_FLOP & 2) == 2)       /* add 2 flops */
            KERNEL2(beta, A[i], alpha);
            //  if ((ERT_FLOP & 16) == 16)     /* add 16 flops */
            REP8(KERNEL2(beta, A[i], alpha));
#endif

#if BW_PCT == 80
            // if ((ERT_FLOP & 8) == 8)       /* add 8 flops */
            REP4(KERNEL2(beta, A[i], alpha));
            //  if ((ERT_FLOP & 16) == 16)     /* add 16 flops */
            REP8(KERNEL2(beta, A[i], alpha));
#endif

#if BW_PCT == 70
            // if ((ERT_FLOP & 4) == 4)       /* add 4 flops */
            REP2(KERNEL2(beta, A[i], alpha));
            // if ((ERT_FLOP & 8) == 8)       /* add 8 flops */
            REP4(KERNEL2(beta, A[i], alpha));
            //  if ((ERT_FLOP & 16) == 16)     /* add 16 flops */
            REP8(KERNEL2(beta, A[i], alpha));

#endif

#if BW_PCT == 60
            // if ((ERT_FLOP & 32) == 32 )    /* add 32 flops */
            REP16(KERNEL2(beta, A[i], alpha));

#endif

#if BW_PCT == 50
            // if ((ERT_FLOP & 2) == 2)       /* add 2 flops */
            KERNEL2(beta, A[i], alpha);
            // if ((ERT_FLOP & 4) == 4)       /* add 4 flops */
            REP2(KERNEL2(beta, A[i], alpha));
            // if ((ERT_FLOP & 32) == 32 )    /* add 32 flops */
            REP16(KERNEL2(beta, A[i], alpha));

#endif

#if BW_PCT == 40
            // if ((ERT_FLOP & 2) == 2)       /* add 2 flops */
            KERNEL2(beta, A[i], alpha);
            // if ((ERT_FLOP & 4) == 4)       /* add 4 flops */
            REP2(KERNEL2(beta, A[i], alpha));
            // if ((ERT_FLOP & 8) == 8)       /* add 8 flops */
            REP4(KERNEL2(beta, A[i], alpha));
            // if ((ERT_FLOP & 32) == 32 )    /* add 32 flops */
            REP16(KERNEL2(beta, A[i], alpha));
#endif

#if BW_PCT == 30
            /// if ((ERT_FLOP & 2) == 2)       /* add 2 flops */
            KERNEL2(beta, A[i], alpha);
            // if ((ERT_FLOP & 4) == 4)       /* add 4 flops */
            REP2(KERNEL2(beta, A[i], alpha));
            // if ((ERT_FLOP & 8) == 8)       /* add 8 flops */
            REP4(KERNEL2(beta, A[i], alpha));
            //  if ((ERT_FLOP & 16) == 16)     /* add 16 flops */
            REP8(KERNEL2(beta, A[i], alpha));
            // if ((ERT_FLOP & 32) == 32 )    /* add 32 flops */
            REP16(KERNEL2(beta, A[i], alpha));
#endif

#if BW_PCT == 20
            // if ((ERT_FLOP & 2) == 2)       /* add 2 flops */
            KERNEL2(beta, A[i], alpha);
            // if ((ERT_FLOP & 16) == 16)     /* add 16 flops */
            REP8(KERNEL2(beta, A[i], alpha));
            // if ((ERT_FLOP & 32) == 32 )    /* add 32 flops */
            REP16(KERNEL2(beta, A[i], alpha));
            // if ((ERT_FLOP & 64) == 64)     /* add 64 flops */
            REP32(KERNEL2(beta, A[i], alpha));
#endif

#if BW_PCT == 10
            // if ((ERT_FLOP & 4) == 4)       /* add 4 flops */
            REP2(KERNEL2(beta, A[i], alpha));
            //  if ((ERT_FLOP & 16) == 16)     /* add 16 flops */
            REP8(KERNEL2(beta, A[i], alpha));
            // if ((ERT_FLOP & 128) == 128)   /* add 128 flops */
            REP64(KERNEL2(beta, A[i], alpha));
#endif

#endif


#ifdef INTENS

#if INTENS == 1
	//#if (ERT_FLOP & 1) == 1       /* add 1 flop */
	KERNEL1(beta,A[i],alpha);

#endif

#if INTENS == 2
	//#if (ERT_FLOP & 2) == 2       /* add 2 flops */
      	KERNEL2(beta,A[i],alpha);

#endif

#if INTENS == 3
//int flop = 4;
//#if (ERT_FLOP & 4) == 4       /* add 4 flops */
      REP2(KERNEL2(beta,A[i],alpha));

#endif

#if INTENS == 4
//int flop = 6;
//#if (ERT_FLOP & 2) == 2       /* add 2 flops */
      KERNEL2(beta,A[i],alpha);
//#if (ERT_FLOP & 4) == 4       /* add 4 flops */
      REP2(KERNEL2(beta,A[i],alpha));

#endif

#if INTENS == 5
//int flop = 8;
//#if (ERT_FLOP & 8) == 8       /* add 8 flops */
      REP4(KERNEL2(beta,A[i],alpha));

#endif

#if INTENS == 6
//int flop = 12;
//#if (ERT_FLOP & 4) == 4       /* add 4 flops */
      REP2(KERNEL2(beta,A[i],alpha));
//#if (ERT_FLOP & 8) == 8       /* add 8 flops */
      REP4(KERNEL2(beta,A[i],alpha));

#endif

#if INTENS == 7 
//int flop = 16;
//#if (ERT_FLOP & 16) == 16     /* add 16 flops */
      REP8(KERNEL2(beta,A[i],alpha));

#endif

#if INTENS == 8
//int flop = 20;

//#if (ERT_FLOP & 4) == 4       /* add 4 flops */
      REP2(KERNEL2(beta,A[i],alpha));

//#if (ERT_FLOP & 16) == 16     /* add 16 flops */
      REP8(KERNEL2(beta,A[i],alpha));

#endif

#if INTENS == 9
//int flop = 28;

//#if (ERT_FLOP & 4) == 4       /* add 4 flops */
      REP2(KERNEL2(beta,A[i],alpha));
//#if (ERT_FLOP & 8) == 8       /* add 8 flops */
      REP4(KERNEL2(beta,A[i],alpha));
//#if (ERT_FLOP & 16) == 16     /* add 16 flops */
      REP8(KERNEL2(beta,A[i],alpha));


#endif

#if INTENS == 10
//int flop = 32;
//#if (ERT_FLOP & 32) == 32     /* add 32 flops */
      REP16(KERNEL2(beta,A[i],alpha));

#endif

#if INTENS == 11
//int flop = 48;
//#if (ERT_FLOP & 16) == 16     /* add 16 flops */
      REP8(KERNEL2(beta,A[i],alpha));
//#if (ERT_FLOP & 32) == 32     /* add 32 flops */
      REP16(KERNEL2(beta,A[i],alpha));

#endif

#if INTENS == 12
//int flop = 64;
//#if (ERT_FLOP & 64) == 64     /* add 64 flops */
      REP32(KERNEL2(beta,A[i],alpha));

#endif

#if INTENS == 13
int flop = 96;
//#if (ERT_FLOP & 32) == 32     /* add 32 flops */
      REP16(KERNEL2(beta,A[i],alpha));
//#if (ERT_FLOP & 64) == 64     /* add 64 flops */
      REP32(KERNEL2(beta,A[i],alpha));

#endif

#if INTENS == 14
//int flop = 128;
//#if (ERT_FLOP & 128) == 128   /* add 128 flops */
      REP64(KERNEL2(beta,A[i],alpha));
#endif

#if INTENS == 15
//int flop = 192;
//#if (ERT_FLOP & 64) == 64     /* add 64 flops */
      REP32(KERNEL2(beta,A[i],alpha));
//#if (ERT_FLOP & 128) == 128   /* add 128 flops */
      REP64(KERNEL2(beta,A[i],alpha));

#endif

#if INTENS == 16
//int flop = 256;
//#if (ERT_FLOP & 256) == 256   /* add 256 flops */
      REP128(KERNEL2(beta,A[i],alpha));

#endif

#if INTENS == 17 
//int flop = 384;
//#if (ERT_FLOP & 128) == 128   /* add 128 flops */
      REP64(KERNEL2(beta,A[i],alpha));
//#if (ERT_FLOP & 256) == 256   /* add 256 flops */
      REP128(KERNEL2(beta,A[i],alpha));
#endif

#if INTENS == 18
int flop = 512;
//#if (ERT_FLOP & 512) == 512   /* add 512 flops */
      REP256(KERNEL2(beta,A[i],alpha));

#endif

#if INTENS == 19
int flop = 768;
//#if (ERT_FLOP & 256) == 256   /* add 256 flops */
      REP128(KERNEL2(beta,A[i],alpha));
//#if (ERT_FLOP & 512) == 512   /* add 512 flops */
      REP256(KERNEL2(beta,A[i],alpha));

#endif

#if INTENS == 20
int flop = 1024;
//#if (ERT_FLOP & 1024) == 1024 /* add 1024 flops */
      REP512(KERNEL2(beta,A[i],alpha));

#endif

#endif
            // if ((ERT_FLOP & 2) == 2)       /* add 2 flops */
            // KERNEL2(beta,A[i],alpha);
            // if ((ERT_FLOP & 4) == 4)       /* add 4 flops */
            //      REP2(KERNEL2(beta,A[i],alpha));
            // if ((ERT_FLOP & 8) == 8)       /* add 8 flops */
            //      REP4(KERNEL2(beta,A[i],alpha));
            //  if ((ERT_FLOP & 16) == 16)     /* add 16 flops */
            //      REP8(KERNEL2(beta,A[i],alpha));
            // if ((ERT_FLOP & 32) == 32 )    /* add 32 flops */
            //      REP16(KERNEL2(beta,A[i],alpha));
            // if ((ERT_FLOP & 64) == 64)     /* add 64 flops */
            //      REP32(KERNEL2(beta,A[i],alpha));
            // if ((ERT_FLOP & 128) == 128)   /* add 128 flops */
            //      REP64(KERNEL2(beta,A[i],alpha));
            // if ((ERT_FLOP & 256) == 256)   /* add 256 flops */
            //      REP128(KERNEL2(beta,A[i],alpha));
            // if ((ERT_FLOP & 512) == 512)   /* add 512 flops */
            //      REP256(KERNEL2(beta,A[i],alpha));
            // if ((ERT_FLOP & 1024) == 1024) /* add 1024 flops */
            //     REP512(KERNEL2(beta,A[i],alpha));
            A[i] = beta;
        }
        alpha = alpha * (1 - 1e-8);
    }
}
double getTime() {
    double time;
    time = omp_get_wtime();
    return time;
}

int main(int argc, char *argv[]) {

    if ( argc > 0){

        for ( int i = 0; i < argc; i++){
/*
            if (argv[i] = "verbose=1")
                verbose = 1;
            if (argv[i] = "verbose=0")
                verbose = 0;
            if (argv[i] = "csv=0")
                csv = 0;
            if (argv[i] = "csv=1")
                csv = 1;


        }
	*/

    }

    key_t shmkey; /*      shared memory key       */
    int shmid;    /*      shared memory id        */

    int *p_2; /*      shared variable         */ /*shared */
    // shmdt (p);shmctl (shmid, IPC_RMID, 0);exit(0);

    /* initialize a shared variable in shared memory */
    // shmkey = ftok ("/home/66m", 5);       /* valid directory name and a
    // number */
    shmkey = ftok("/dev/null", 5); /* valid directory name and a number */
    // printf ("shmkey for p = %d\n", shmkey);
    shmid = shmget(shmkey, sizeof(int), 0644 | IPC_CREAT);
    if (shmid < 0) { /* shared memory error check */
        perror("shmget\n");
        exit(1);
    }
    // pthread_mutex_t *m;
    // Mutex a(m,false);
    p_2 = (int *)shmat(shmid, NULL, 0); /* attach p to shared memory */
                                      //*p = 0;
    // printf ("p=%d is allocated in shared memory.\n\n", *p);

    int rank = 0;
    int nprocs = 1;
    int nthreads = 1;
    int id = 0;

    uint64_t TSIZE = 1 << 30;
    uint64_t PSIZE = TSIZE / nprocs;

    double *buf = (double *)malloc(PSIZE);

    if (buf == NULL) {
        fprintf(stderr, "Out of memory!\n");
        return -1;
    }
#pragma omp parallel private(id)
    {
        id = omp_get_thread_num();
        // std::cout << id << " thread" << std::endl;
        nthreads = omp_get_num_threads();

        uint64_t nsize = PSIZE / nthreads;
        nsize = nsize & (~(64 - 1));
        nsize = nsize / sizeof(double);
        uint64_t nid = nsize * id;

        // initialize small chunck of buffer within each thread
        initialize(nsize, &buf[nid], 1.0);

        double startTime, endTime;
        uint64_t n, nNew;
        uint64_t t;
        int bytes_per_elem;
        int mem_accesses_per_elem;
        double seconds = 0;
        uint64_t working_set_size = 0;
        uint64_t total_bytes = 0;
        uint64_t total_flops = 0;

        n = 1 << 22;
	//n = n / nthreads;

#if INFIN_LOOP < 1
        //int lim = 100;
        //int lim = 35;
        int lim = 100;
#ifdef LIM
        lim = LIM; 
#endif
        while (n <= nsize) { // working set - nsize
        //std::cout << "nsize: " << nsize << " value of n: " << n << std::endl;
#else
        int lim = 89;
        while (1) { // working set - nsize
#endif
            uint64_t ntrials = nsize / n;
            if (ntrials < 1)
                ntrials = 1;
	
	    for (int x = 0; x <= argc; x ++){
            for (t = 0; t <= lim; t = t + 1) { // working set - ntrials
            //---for (t = lim - 35; t <= lim; t = t + 1) { // working set - ntrials
#pragma omp barrier

                if (id == 0 && t == (lim - 19))
                    *p_2 += 1;
                if ((id == 0) && (rank == 0)) {
                    startTime = getTime();
                }
                // C-code
                kernel11(n, t, &buf[nid], &bytes_per_elem,
                       &mem_accesses_per_elem);

#pragma omp barrier

                if ((id == 0) && (rank == 0) && (t > (lim-20))) {

                    // if ((id == 0) && (rank == 0) ) {
                    int flop = 48;
                    endTime = getTime();
                    seconds += (double)(endTime - startTime);
                    working_set_size = n * nthreads * nprocs;
                    total_bytes += t * working_set_size * bytes_per_elem *
                                   mem_accesses_per_elem;
                    total_flops += t * working_set_size * flop;

                    //std::cout << "nthreads: " << nthreads << " value of n: " << n << " working set size: " << working_set_size << "total bytes: " << total_bytes << " total_flops: " << total_flops << std::endl;

                    // total_flops += t * working_set_size * ERT_FLOP;
                }
                if ((id == 0) && (rank == 0) && (t == lim)) {
                    // if ((id == 0) && (rank == 0) ) {
                    /*endTime = getTime();
                    seconds = (double)(endTime - startTime);
                    working_set_size = n * nthreads * nprocs;
                    total_bytes = t * working_set_size * bytes_per_elem *
			    mem_accesses_per_elem; total_flops = t * working_set_size * ERT_FLOP;
			    // nsize; trials; microseconds; bytes; single thread bandwidth; total
			    bandwidth printf("%12" PRIu64 " %12" PRIu64 " %15.3lf %12" PRIu64 " %12"
			    PRIu64 "\n", working_set_size * bytes_per_elem, t, seconds, total_bytes,total_flops);*/
#if INFIN_LOOP < 1

                    printf("BadnWindth : %15.3lf\n",
                           total_bytes * 1.0 / seconds / 1024 / 1024 / 1024);
                    printf("Total Bytes: %15" PRIu64 "\n", total_bytes);
                    printf("Total flops: %15" PRIu64 "\n", total_flops);
                    printf("Total time : %15.6lf \n", seconds);
#else
#endif
               } // print

            } // working set - ntrials
            seconds = 0;
            working_set_size = 0;
            total_bytes = 0;
            total_flops = 0;


            for (t = lim - 19; t <= lim; t = t + 1) { // working set - ntrials
#pragma omp barrier

                if ((id == 0) && (rank == 0)) {
                    startTime = getTime();
                }
                // C-code
                kernel8(n, t, &buf[nid], &bytes_per_elem,
                       &mem_accesses_per_elem);

#pragma omp barrier

                if ((id == 0) && (rank == 0) && (t > (lim-20))) {

                    // if ((id == 0) && (rank == 0) ) {
                    int flop = 20;
                    endTime = getTime();
                    seconds += (double)(endTime - startTime);
                    working_set_size = n * nthreads * nprocs;
                    total_bytes += t * working_set_size * bytes_per_elem *
                                   mem_accesses_per_elem;
                    total_flops += t * working_set_size * flop;

                    //std::cout << "nthreads: " << nthreads << " value of n: " << n << " working set size: " << working_set_size << "total bytes: " << total_bytes << " total_flops: " << total_flops << std::endl;

                    // total_flops += t * working_set_size * ERT_FLOP;
                }
                if ((id == 0) && (rank == 0) && (t == lim)) {
                    // if ((id == 0) && (rank == 0) ) {
                    /*endTime = getTime();
                    seconds = (double)(endTime - startTime);
                    working_set_size = n * nthreads * nprocs;
                    total_bytes = t * working_set_size * bytes_per_elem *
			    mem_accesses_per_elem; total_flops = t * working_set_size * ERT_FLOP;
			    // nsize; trials; microseconds; bytes; single thread bandwidth; total
			    bandwidth printf("%12" PRIu64 " %12" PRIu64 " %15.3lf %12" PRIu64 " %12"
			    PRIu64 "\n", working_set_size * bytes_per_elem, t, seconds, total_bytes,total_flops);*/
#if INFIN_LOOP < 1

                    printf("BadnWindth : %15.3lf\n",
                           total_bytes * 1.0 / seconds / 1024 / 1024 / 1024);
                    printf("Total Bytes: %15" PRIu64 "\n", total_bytes);
                    printf("Total flops: %15" PRIu64 "\n", total_flops);
                    printf("Total time : %15.6lf \n", seconds);
#else
#endif
               } // print

            } // working set - ntrials

            seconds = 0;
            working_set_size = 0;
            total_bytes = 0;
            total_flops = 0;


            for (t = lim - 19; t <= lim; t = t + 1) { // working set - ntrials
#pragma omp barrier

                if ((id == 0) && (rank == 0)) {
                    startTime = getTime();
                }
                // C-code
                kernel6(n, t, &buf[nid], &bytes_per_elem,
                       &mem_accesses_per_elem);

#pragma omp barrier

                if ((id == 0) && (rank == 0) && (t > (lim-20))) {

                    // if ((id == 0) && (rank == 0) ) {
                    int flop = 12;
                    endTime = getTime();
                    seconds += (double)(endTime - startTime);
                    working_set_size = n * nthreads * nprocs;
                    total_bytes += t * working_set_size * bytes_per_elem *
                                   mem_accesses_per_elem;
                    total_flops += t * working_set_size * flop;

                    //std::cout << "nthreads: " << nthreads << " value of n: " << n << " working set size: " << working_set_size << "total bytes: " << total_bytes << " total_flops: " << total_flops << std::endl;

                    // total_flops += t * working_set_size * ERT_FLOP;
                }
                if ((id == 0) && (rank == 0) && (t == lim)) {
                    // if ((id == 0) && (rank == 0) ) {
                    /*endTime = getTime();
                    seconds = (double)(endTime - startTime);
                    working_set_size = n * nthreads * nprocs;
                    total_bytes = t * working_set_size * bytes_per_elem *
			    mem_accesses_per_elem; total_flops = t * working_set_size * ERT_FLOP;
			    // nsize; trials; microseconds; bytes; single thread bandwidth; total
			    bandwidth printf("%12" PRIu64 " %12" PRIu64 " %15.3lf %12" PRIu64 " %12"
			    PRIu64 "\n", working_set_size * bytes_per_elem, t, seconds, total_bytes,total_flops);*/
#if INFIN_LOOP < 1

                    printf("BadnWindth : %15.3lf\n",
                           total_bytes * 1.0 / seconds / 1024 / 1024 / 1024);
                    printf("Total Bytes: %15" PRIu64 "\n", total_bytes);
                    printf("Total flops: %15" PRIu64 "\n", total_flops);
                    printf("Total time : %15.6lf \n", seconds);
#else
#endif
               } // print

            } // working set - ntrials




#if INFIN_LOOP < 1
            /// just to discontinue after running once
            n = nsize + 1;
            if (id == 0)
                *p_2 += 1;

	    //ii += 1;
	    //n = 1 << ii;
#else
#endif

            /*nNew = 2 * n;
            if (nNew == n) {
                            nNew = n+1;
            }

            n = nNew;*/

        } // working set - nsize

    } // parallel region

    free(buf);

    /*printf("\n");
    printf("META_DATA\n");
    printf("FLOPS          %d\n", ERT_FLOP);

    printf("OPENMP_THREADS %d\n", nthreads); */

    shmdt(p);
    shmctl(shmid, IPC_RMID, 0);

    return 0;
}
/*if ((id == 0) && (rank == 0) && (t > 90)) {
        //if ((id == 0) && (rank == 0) ) {
                endTime = getTime();
                double seconds = (double)(endTime - startTime);
                uint64_t working_set_size = n * nthreads * nprocs;
                uint64_t total_bytes = t * working_set_size * bytes_per_elem *
mem_accesses_per_elem; uint64_t total_flops = t * working_set_size * ERT_FLOP;
// nsize; trials; microseconds; bytes; single thread bandwidth; total bandwidth
                *//*printf("%12" PRIu64 " %12" PRIu64 " %15.3lf %12" PRIu64 " %12" PRIu64 "\n",
							       working_set_size * bytes_per_elem,
							       t,
							       seconds,
							       total_bytes,
							       total_flops);*/
/*
                                                        printf("BadnWindth :
   %15.3lf\n",total_bytes*1.0/seconds/1024/1024/1024); printf("Total Bytes: %15"
   PRIu64"\n",total_bytes); printf("Total flops: %15" PRIu64"\n",total_flops);
                                                        printf("Total time :
   %15.6lf \n",seconds);
                                                }*/
