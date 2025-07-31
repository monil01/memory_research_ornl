#include <cuda_runtime.h>
#include <inttypes.h>
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <sys/shm.h>
#include <unistd.h>

int flop = 0;
// helper functions and utilities to work with CUDA
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

#define KERNEL2(a, b, c) ((a) = (a) * (b) + (c))
#define KERNEL1(a, b, c) ((a) = (b) + (c))

int gpu_blocks = 512;
int gpu_threads = 512;

#ifdef BW_PCT

#if BW_PCT == 100
int flop = 2;
#endif
#if BW_PCT == 90
int flop = 4;
#endif

#if BW_PCT == 80
int flop = 6;
#endif

#if BW_PCT == 70
int flop = 8;
#endif

#if BW_PCT == 60
int flop = 8;

#endif

#if BW_PCT == 50
int flop = 10;

#endif

#if BW_PCT == 40
int flop = 12;
#endif

#if BW_PCT == 30
int flop = 16;
#endif

#if BW_PCT == 20
int flop = 24;
#endif

#if BW_PCT == 10
int flop = 52;
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

void gpuKernel(uint64_t nsize, uint64_t ntrials, double *__restrict__ array,
               int *bytes_per_elem, int *mem_accesses_per_elem);

__global__ void block_stride(uint64_t ntrials, uint64_t nsize, double *A) {
    uint64_t total_thr = gridDim.x * blockDim.x;
    uint64_t elem_per_thr = (nsize + (total_thr - 1)) / total_thr;
    uint64_t blockOffset = blockIdx.x * blockDim.x;

    uint64_t start_idx = blockOffset + threadIdx.x;
    uint64_t end_idx = start_idx + elem_per_thr * total_thr;
    uint64_t stride_idx = total_thr;

    if (start_idx > nsize) {
        start_idx = nsize;
    }

    if (end_idx > nsize) {
        end_idx = nsize;
    }

    double alpha = 0.5;
    uint64_t i, j;
    for (j = 0; j < ntrials; ++j) {
        for (i = start_idx; i < end_idx; i += stride_idx) {
            double beta = 0.8;

#ifdef BW_PCT
#if BW_PCT == 100

            /* add 1 flop */
            // KERNEL1(beta,A[i],alpha);
            // KERNEL1(beta,A[i],alpha);
            /* add 2 flops */
            KERNEL2(beta, A[i], alpha);
            /* add 4 flops */
            // REP2(KERNEL2(beta,A[i],alpha));

            /* add 8 flops */
            // REP4(KERNEL2(beta,A[i],alpha));
            /* add 16 flops */
            // REP8(KERNEL2(beta,A[i],alpha));
            /* add 32 flops */
            // REP16(KERNEL2(beta,A[i],alpha));
            /* add 64 flops */
            // REP32(KERNEL2(beta,A[i],alpha));
            /* add 128 flops */
            // REP64(KERNEL2(beta,A[i],alpha));
            /* add 256 flops */
            // REP128(KERNEL2(beta,A[i],alpha));
            /* add 512 flops */
            // REP256(KERNEL2(beta,A[i],alpha));
            /* add 1024 flops */
            // REP512(KERNEL2(beta,A[i],alpha));

#endif
#if BW_PCT == 90
            /* add 1 flop */
            // KERNEL1(beta,A[i],alpha);
            // KERNEL1(beta,A[i],alpha);
            /* add 2 flops */
            // KERNEL2(beta,A[i],alpha);
            /* add 4 flops */
            REP2(KERNEL2(beta, A[i], alpha));

            /* add 8 flops */
            // REP4(KERNEL2(beta,A[i],alpha));
            /* add 16 flops */
            // REP8(KERNEL2(beta,A[i],alpha));
            /* add 32 flops */
            // REP16(KERNEL2(beta,A[i],alpha));
            /* add 64 flops */
            // REP32(KERNEL2(beta,A[i],alpha));
            /* add 128 flops */
            // REP64(KERNEL2(beta,A[i],alpha));
            /* add 256 flops */
            // REP128(KERNEL2(beta,A[i],alpha));
            /* add 512 flops */
            // REP256(KERNEL2(beta,A[i],alpha));
            /* add 1024 flops */
            // REP512(KERNEL2(beta,A[i],alpha));

#endif

#if BW_PCT == 80
            /* add 1 flop */
            // KERNEL1(beta,A[i],alpha);
            // KERNEL1(beta,A[i],alpha);
            /* add 2 flops */
            KERNEL2(beta, A[i], alpha);
            /* add 4 flops */
            REP2(KERNEL2(beta, A[i], alpha));

            /* add 8 flops */
            // REP4(KERNEL2(beta,A[i],alpha));
            /* add 16 flops */
            // REP8(KERNEL2(beta,A[i],alpha));
            /* add 32 flops */
            // REP16(KERNEL2(beta,A[i],alpha));
            /* add 64 flops */
            // REP32(KERNEL2(beta,A[i],alpha));
            /* add 128 flops */
            // REP64(KERNEL2(beta,A[i],alpha));
            /* add 256 flops */
            // REP128(KERNEL2(beta,A[i],alpha));
            /* add 512 flops */
            // REP256(KERNEL2(beta,A[i],alpha));
            /* add 1024 flops */
            // REP512(KERNEL2(beta,A[i],alpha));

#endif

#if BW_PCT == 70
            /* add 1 flop */
            // KERNEL1(beta,A[i],alpha);
            // KERNEL1(beta,A[i],alpha);
            /* add 2 flops */
            // KERNEL2(beta,A[i],alpha);
            /* add 4 flops */
            // REP2(KERNEL2(beta,A[i],alpha));
            // REP2(KERNEL2(beta,A[i],alpha));

            /* add 8 flops */
            REP4(KERNEL2(beta, A[i], alpha));
            /* add 16 flops */
            // REP8(KERNEL2(beta,A[i],alpha));
            /* add 32 flops */
            // REP16(KERNEL2(beta,A[i],alpha));
            /* add 64 flops */
            // REP32(KERNEL2(beta,A[i],alpha));
            /* add 128 flops */
            // REP64(KERNEL2(beta,A[i],alpha));
            /* add 256 flops */
            // REP128(KERNEL2(beta,A[i],alpha));
            /* add 512 flops */
            // REP256(KERNEL2(beta,A[i],alpha));
            /* add 1024 flops */
            // REP512(KERNEL2(beta,A[i],alpha));

#endif

#if BW_PCT == 60
            /* add 1 flop */
            // KERNEL1(beta,A[i],alpha);
            // KERNEL1(beta,A[i],alpha);
            /* add 2 flops */
            // KERNEL2(beta,A[i],alpha);
            // KERNEL2(beta,A[i],alpha);
            /* add 4 flops */
            // REP2(KERNEL2(beta,A[i],alpha));

            /* add 8 flops */
            REP4(KERNEL2(beta, A[i], alpha));
            /* add 16 flops */
            // REP8(KERNEL2(beta,A[i],alpha));
            /* add 32 flops */
            // REP16(KERNEL2(beta,A[i],alpha));
            /* add 64 flops */
            // REP32(KERNEL2(beta,A[i],alpha));
            /* add 128 flops */
            // REP64(KERNEL2(beta,A[i],alpha));
            /* add 256 flops */
            // REP128(KERNEL2(beta,A[i],alpha));
            /* add 512 flops */
            // REP256(KERNEL2(beta,A[i],alpha));
            /* add 1024 flops */
            // REP512(KERNEL2(beta,A[i],alpha));

#endif

#if BW_PCT == 50
            /* add 1 flop */
            // KERNEL1(beta,A[i],alpha);
            // KERNEL1(beta,A[i],alpha);
            /* add 2 flops */
            KERNEL2(beta, A[i], alpha);
            /* add 4 flops */
            // REP2(KERNEL2(beta,A[i],alpha));

            /* add 8 flops */
            REP4(KERNEL2(beta, A[i], alpha));
            /* add 16 flops */
            // REP8(KERNEL2(beta,A[i],alpha));
            /* add 32 flops */
            // REP16(KERNEL2(beta,A[i],alpha));
            /* add 64 flops */
            // REP32(KERNEL2(beta,A[i],alpha));
            /* add 128 flops */
            // REP64(KERNEL2(beta,A[i],alpha));
            /* add 256 flops */
            // REP128(KERNEL2(beta,A[i],alpha));
            /* add 512 flops */
            // REP256(KERNEL2(beta,A[i],alpha));
            /* add 1024 flops */
            // REP512(KERNEL2(beta,A[i],alpha));

#endif

#if BW_PCT == 40
            /* add 1 flop */
            // KERNEL1(beta,A[i],alpha);
            // KERNEL1(beta,A[i],alpha);
            /* add 2 flops */
            // KERNEL2(beta,A[i],alpha);
            /* add 4 flops */
            REP2(KERNEL2(beta, A[i], alpha));
            /* add 8 flops */
            REP4(KERNEL2(beta, A[i], alpha));
            /* add 16 flops */
            // REP8(KERNEL2(beta,A[i],alpha));
            /* add 32 flops */
            // REP16(KERNEL2(beta,A[i],alpha));
            /* add 64 flops */
            // REP32(KERNEL2(beta,A[i],alpha));
            /* add 128 flops */
            // REP64(KERNEL2(beta,A[i],alpha));
            /* add 256 flops */
            // REP128(KERNEL2(beta,A[i],alpha));
            /* add 512 flops */
            // REP256(KERNEL2(beta,A[i],alpha));
            /* add 1024 flops */
            // REP512(KERNEL2(beta,A[i],alpha));

#endif

#if BW_PCT == 30
            /* add 1 flop */
            // KERNEL1(beta,A[i],alpha);
            // KERNEL1(beta,A[i],alpha);
            /* add 2 flops */
            // KERNEL2(beta,A[i],alpha);
            /* add 4 flops */
            // REP2(KERNEL2(beta,A[i],alpha));

            /* add 8 flops */
            // REP4(KERNEL2(beta,A[i],alpha));
            /* add 16 flops */
            REP8(KERNEL2(beta, A[i], alpha));
            /* add 32 flops */
            // REP16(KERNEL2(beta,A[i],alpha));
            /* add 64 flops */
            // REP32(KERNEL2(beta,A[i],alpha));
            /* add 128 flops */
            // REP64(KERNEL2(beta,A[i],alpha));
            /* add 256 flops */
            // REP128(KERNEL2(beta,A[i],alpha));
            /* add 512 flops */
            // REP256(KERNEL2(beta,A[i],alpha));
            /* add 1024 flops */
            // REP512(KERNEL2(beta,A[i],alpha));

#endif

#if BW_PCT == 20
            /* add 1 flop */
            // KERNEL1(beta,A[i],alpha);
            // KERNEL1(beta,A[i],alpha);
            /* add 2 flops */
            // KERNEL2(beta,A[i],alpha);
            /* add 4 flops */
            // REP2(KERNEL2(beta,A[i],alpha));

            /* add 8 flops */
            REP4(KERNEL2(beta, A[i], alpha));
            /* add 16 flops */
            REP8(KERNEL2(beta, A[i], alpha));
            /* add 32 flops */
            // REP16(KERNEL2(beta,A[i],alpha));
            /* add 64 flops */
            // REP32(KERNEL2(beta,A[i],alpha));
            /* add 128 flops */
            // REP64(KERNEL2(beta,A[i],alpha));
            /* add 256 flops */
            // REP128(KERNEL2(beta,A[i],alpha));
            /* add 512 flops */
            // REP256(KERNEL2(beta,A[i],alpha));
            /* add 1024 flops */
            // REP512(KERNEL2(beta,A[i],alpha));

#endif

#if BW_PCT == 10
            /* add 1 flop */
            // KERNEL1(beta,A[i],alpha);
            // KERNEL1(beta,A[i],alpha);
            /* add 2 flops */
            // KERNEL2(beta,A[i],alpha);
            /* add 4 flops */
            REP2(KERNEL2(beta, A[i], alpha));

            /* add 8 flops */
            // REP4(KERNEL2(beta,A[i],alpha));
            /* add 16 flops */
            REP8(KERNEL2(beta, A[i], alpha));
            /* add 32 flops */
            REP16(KERNEL2(beta, A[i], alpha));
            /* add 64 flops */
            // REP32(KERNEL2(beta,A[i],alpha));
            /* add 128 flops */
            // REP64(KERNEL2(beta,A[i],alpha));
            /* add 256 flops */
            // REP128(KERNEL2(beta,A[i],alpha));
            /* add 512 flops */
            // REP256(KERNEL2(beta,A[i],alpha));
            /* add 1024 flops */
            // REP512(KERNEL2(beta,A[i],alpha));

#endif

#endif

#ifdef INTENS

#if INTENS == 1
            //#if (ERT_FLOP & 1) == 1       /* add 1 flop */
            KERNEL1(beta, A[i], alpha);

#endif

#if INTENS == 2
            //#if (ERT_FLOP & 2) == 2       /* add 2 flops */
            KERNEL2(beta, A[i], alpha);

#endif

#if INTENS == 3
            // int flop = 4;
            //#if (ERT_FLOP & 4) == 4       /* add 4 flops */
            REP2(KERNEL2(beta, A[i], alpha));

#endif

#if INTENS == 4
            // int flop = 6;
            //#if (ERT_FLOP & 2) == 2       /* add 2 flops */
            KERNEL2(beta, A[i], alpha);
            //#if (ERT_FLOP & 4) == 4       /* add 4 flops */
            REP2(KERNEL2(beta, A[i], alpha));

#endif

#if INTENS == 5
            // int flop = 8;
            //#if (ERT_FLOP & 8) == 8       /* add 8 flops */
            REP4(KERNEL2(beta, A[i], alpha));

#endif

#if INTENS == 6
            // int flop = 12;
            //#if (ERT_FLOP & 4) == 4       /* add 4 flops */
            REP2(KERNEL2(beta, A[i], alpha));
            //#if (ERT_FLOP & 8) == 8       /* add 8 flops */
            REP4(KERNEL2(beta, A[i], alpha));

#endif

#if INTENS == 7
            // int flop = 16;
            //#if (ERT_FLOP & 16) == 16     /* add 16 flops */
            REP8(KERNEL2(beta, A[i], alpha));

#endif

#if INTENS == 8
            // int flop = 20;

            //#if (ERT_FLOP & 4) == 4       /* add 4 flops */
            REP2(KERNEL2(beta, A[i], alpha));

            //#if (ERT_FLOP & 16) == 16     /* add 16 flops */
            REP8(KERNEL2(beta, A[i], alpha));

#endif

#if INTENS == 9
            // int flop = 28;

            //#if (ERT_FLOP & 4) == 4       /* add 4 flops */
            REP2(KERNEL2(beta, A[i], alpha));
            //#if (ERT_FLOP & 8) == 8       /* add 8 flops */
            REP4(KERNEL2(beta, A[i], alpha));
            //#if (ERT_FLOP & 16) == 16     /* add 16 flops */
            REP8(KERNEL2(beta, A[i], alpha));

#endif

#if INTENS == 10
            // int flop = 32;
            //#if (ERT_FLOP & 32) == 32     /* add 32 flops */
            REP16(KERNEL2(beta, A[i], alpha));

#endif

#if INTENS == 11
            // int flop = 48;
            //#if (ERT_FLOP & 16) == 16     /* add 16 flops */
            REP8(KERNEL2(beta, A[i], alpha));
            //#if (ERT_FLOP & 32) == 32     /* add 32 flops */
            REP16(KERNEL2(beta, A[i], alpha));

#endif

#if INTENS == 12
            // int flop = 64;
            //#if (ERT_FLOP & 64) == 64     /* add 64 flops */
            REP32(KERNEL2(beta, A[i], alpha));

#endif

#if INTENS == 13
            // int flop = 96;
            //#if (ERT_FLOP & 32) == 32     /* add 32 flops */
            REP16(KERNEL2(beta, A[i], alpha));
            //#if (ERT_FLOP & 64) == 64     /* add 64 flops */
            REP32(KERNEL2(beta, A[i], alpha));

#endif

#if INTENS == 14
            // int flop = 128;
            //#if (ERT_FLOP & 128) == 128   /* add 128 flops */
            REP64(KERNEL2(beta, A[i], alpha));
#endif

#if INTENS == 15
            // int flop = 192;
            //#if (ERT_FLOP & 64) == 64     /* add 64 flops */
            REP32(KERNEL2(beta, A[i], alpha));
            //#if (ERT_FLOP & 128) == 128   /* add 128 flops */
            REP64(KERNEL2(beta, A[i], alpha));

#endif

#if INTENS == 16
            // int flop = 256;
            //#if (ERT_FLOP & 256) == 256   /* add 256 flops */
            REP128(KERNEL2(beta, A[i], alpha));

#endif

#if INTENS == 17
            // int flop = 384;
            //#if (ERT_FLOP & 128) == 128   /* add 128 flops */
            REP64(KERNEL2(beta, A[i], alpha));
            //#if (ERT_FLOP & 256) == 256   /* add 256 flops */
            REP128(KERNEL2(beta, A[i], alpha));
#endif

#if INTENS == 18
            int flop = 512;
            //#if (ERT_FLOP & 512) == 512   /* add 512 flops */
            REP256(KERNEL2(beta, A[i], alpha));

#endif

#if INTENS == 19
            int flop = 768;
            //#if (ERT_FLOP & 256) == 256   /* add 256 flops */
            REP128(KERNEL2(beta, A[i], alpha));
            //#if (ERT_FLOP & 512) == 512   /* add 512 flops */
            REP256(KERNEL2(beta, A[i], alpha));

#endif

#if INTENS == 20
            int flop = 1024;
            //#if (ERT_FLOP & 1024) == 1024 /* add 1024 flops */
            REP512(KERNEL2(beta, A[i], alpha));

#endif

#endif

            /* add 1 flop */
            // KERNEL1(beta,A[i],alpha);
            // KERNEL1(beta,A[i],alpha);
            /* add 2 flops */
            // KERNEL2(beta,A[i],alpha);
            /* add 4 flops */
            // REP2(KERNEL2(beta,A[i],alpha));
            /* add 8 flops */
            // REP4(KERNEL2(beta,A[i],alpha));
            /* add 16 flops */
            // REP8(KERNEL2(beta,A[i],alpha));
            /* add 32 flops */
            // REP16(KERNEL2(beta,A[i],alpha));
            /* add 64 flops */
            // REP32(KERNEL2(beta,A[i],alpha));
            /* add 128 flops */
            // REP64(KERNEL2(beta,A[i],alpha));
            /* add 256 flops */
            // REP128(KERNEL2(beta,A[i],alpha));
            /* add 512 flops */
            // REP256(KERNEL2(beta,A[i],alpha));
            /* add 1024 flops */
            // REP512(KERNEL2(beta,A[i],alpha));

            A[i] = beta;
        }
        alpha = alpha * (1 - 1e-8);
    }
}

__global__ void block_stride5(uint64_t ntrials, uint64_t nsize, double *A) {
    uint64_t total_thr = gridDim.x * blockDim.x;
    uint64_t elem_per_thr = (nsize + (total_thr - 1)) / total_thr;
    uint64_t blockOffset = blockIdx.x * blockDim.x;

    uint64_t start_idx = blockOffset + threadIdx.x;
    uint64_t end_idx = start_idx + elem_per_thr * total_thr;
    uint64_t stride_idx = total_thr;

    if (start_idx > nsize) {
        start_idx = nsize;
    }

    if (end_idx > nsize) {
        end_idx = nsize;
    }

    double alpha = 0.5;
    uint64_t i, j;
    for (j = 0; j < ntrials; ++j) {
        for (i = start_idx; i < end_idx; i += stride_idx) {
            double beta = 0.8;

            //#if (ERT_FLOP & 16) == 16     /* add 16 flops */
            REP8(KERNEL2(beta, A[i], alpha));
            //#if (ERT_FLOP & 32) == 32     /* add 32 flops */
            REP16(KERNEL2(beta, A[i], alpha));

            A[i] = beta;
        }
        alpha = alpha * (1 - 1e-8);
    }
}

void gpuKernel5(uint64_t nsize, uint64_t ntrials, double *__restrict__ A,
                int *bytes_per_elem, int *mem_accesses_per_elem) {
    *bytes_per_elem = sizeof(*A);
    *mem_accesses_per_elem = 2;
    flop = 48;
    // gpu_blocks = (nsize+1023)/1024;
    block_stride5<<<gpu_blocks, gpu_threads>>>(ntrials, nsize, A);
}

__global__ void block_stride4(uint64_t ntrials, uint64_t nsize, double *A) {
    uint64_t total_thr = gridDim.x * blockDim.x;
    uint64_t elem_per_thr = (nsize + (total_thr - 1)) / total_thr;
    uint64_t blockOffset = blockIdx.x * blockDim.x;

    uint64_t start_idx = blockOffset + threadIdx.x;
    uint64_t end_idx = start_idx + elem_per_thr * total_thr;
    uint64_t stride_idx = total_thr;

    if (start_idx > nsize) {
        start_idx = nsize;
    }

    if (end_idx > nsize) {
        end_idx = nsize;
    }

    double alpha = 0.5;
    uint64_t i, j;
    for (j = 0; j < ntrials; ++j) {
        for (i = start_idx; i < end_idx; i += stride_idx) {
            double beta = 0.8;

            // int flop = 20;

            //#if (ERT_FLOP & 4) == 4       /* add 4 flops */
            REP2(KERNEL2(beta, A[i], alpha));

            //#if (ERT_FLOP & 16) == 16     /* add 16 flops */
            REP8(KERNEL2(beta, A[i], alpha));

            A[i] = beta;
        }
        alpha = alpha * (1 - 1e-8);
    }
}

void gpuKernel4(uint64_t nsize, uint64_t ntrials, double *__restrict__ A,
                int *bytes_per_elem, int *mem_accesses_per_elem) {
    *bytes_per_elem = sizeof(*A);
    *mem_accesses_per_elem = 2;
    flop = 20;
    // gpu_blocks = (nsize+1023)/1024;
    block_stride4<<<gpu_blocks, gpu_threads>>>(ntrials, nsize, A);
}

__global__ void block_stride3(uint64_t ntrials, uint64_t nsize, double *A) {
    uint64_t total_thr = gridDim.x * blockDim.x;
    uint64_t elem_per_thr = (nsize + (total_thr - 1)) / total_thr;
    uint64_t blockOffset = blockIdx.x * blockDim.x;

    uint64_t start_idx = blockOffset + threadIdx.x;
    uint64_t end_idx = start_idx + elem_per_thr * total_thr;
    uint64_t stride_idx = total_thr;

    if (start_idx > nsize) {
        start_idx = nsize;
    }

    if (end_idx > nsize) {
        end_idx = nsize;
    }

    double alpha = 0.5;
    uint64_t i, j;
    for (j = 0; j < ntrials; ++j) {
        for (i = start_idx; i < end_idx; i += stride_idx) {
            double beta = 0.8;

            // int flop = 12;
            //#if (ERT_FLOP & 4) == 4       /* add 4 flops */
            REP2(KERNEL2(beta, A[i], alpha));
            //#if (ERT_FLOP & 8) == 8       /* add 8 flops */
            REP4(KERNEL2(beta, A[i], alpha));

            A[i] = beta;
        }
        alpha = alpha * (1 - 1e-8);
    }
}

void gpuKernel3(uint64_t nsize, uint64_t ntrials, double *__restrict__ A,
                int *bytes_per_elem, int *mem_accesses_per_elem) {
    *bytes_per_elem = sizeof(*A);
    *mem_accesses_per_elem = 2;
    flop = 12;
    // gpu_blocks = (nsize+1023)/1024;
    block_stride3<<<gpu_blocks, gpu_threads>>>(ntrials, nsize, A);
}

__global__ void block_stride2(uint64_t ntrials, uint64_t nsize, double *A) {
    uint64_t total_thr = gridDim.x * blockDim.x;
    uint64_t elem_per_thr = (nsize + (total_thr - 1)) / total_thr;
    uint64_t blockOffset = blockIdx.x * blockDim.x;

    uint64_t start_idx = blockOffset + threadIdx.x;
    uint64_t end_idx = start_idx + elem_per_thr * total_thr;
    uint64_t stride_idx = total_thr;

    if (start_idx > nsize) {
        start_idx = nsize;
    }

    if (end_idx > nsize) {
        end_idx = nsize;
    }

    double alpha = 0.5;
    uint64_t i, j;
    for (j = 0; j < ntrials; ++j) {
        for (i = start_idx; i < end_idx; i += stride_idx) {
            double beta = 0.8;

            // int flop = 6;
            //#if (ERT_FLOP & 2) == 2       /* add 2 flops */
            KERNEL2(beta, A[i], alpha);
            //#if (ERT_FLOP & 4) == 4       /* add 4 flops */
            REP2(KERNEL2(beta, A[i], alpha));

            A[i] = beta;
        }
        alpha = alpha * (1 - 1e-8);
    }
}

void gpuKernel2(uint64_t nsize, uint64_t ntrials, double *__restrict__ A,
                int *bytes_per_elem, int *mem_accesses_per_elem) {
    *bytes_per_elem = sizeof(*A);
    *mem_accesses_per_elem = 2;
    flop = 6;
    // gpu_blocks = (nsize+1023)/1024;
    block_stride2<<<gpu_blocks, gpu_threads>>>(ntrials, nsize, A);
}

__global__ void block_stride1(uint64_t ntrials, uint64_t nsize, double *A) {
    uint64_t total_thr = gridDim.x * blockDim.x;
    uint64_t elem_per_thr = (nsize + (total_thr - 1)) / total_thr;
    uint64_t blockOffset = blockIdx.x * blockDim.x;

    uint64_t start_idx = blockOffset + threadIdx.x;
    uint64_t end_idx = start_idx + elem_per_thr * total_thr;
    uint64_t stride_idx = total_thr;

    if (start_idx > nsize) {
        start_idx = nsize;
    }

    if (end_idx > nsize) {
        end_idx = nsize;
    }

    double alpha = 0.5;
    uint64_t i, j;
    for (j = 0; j < ntrials; ++j) {
        for (i = start_idx; i < end_idx; i += stride_idx) {
            double beta = 0.8;

            //#if (ERT_FLOP & 1) == 1       /* add 1 flop */
            KERNEL1(beta, A[i], alpha);

            A[i] = beta;
        }
        alpha = alpha * (1 - 1e-8);
    }
}

void gpuKernel1(uint64_t nsize, uint64_t ntrials, double *__restrict__ A,
                int *bytes_per_elem, int *mem_accesses_per_elem) {
    *bytes_per_elem = sizeof(*A);
    *mem_accesses_per_elem = 2;
    flop = 1;
    // gpu_blocks = (nsize+1023)/1024;
    block_stride1<<<gpu_blocks, gpu_threads>>>(ntrials, nsize, A);
}

__global__ void block_stride_triad(uint64_t ntrials, uint64_t nsize, double *A) {
    uint64_t total_thr = gridDim.x * blockDim.x;
    uint64_t elem_per_thr = (nsize + (total_thr - 1)) / total_thr;
    uint64_t blockOffset = blockIdx.x * blockDim.x;

    uint64_t start_idx = blockOffset + threadIdx.x;
    uint64_t end_idx = start_idx + elem_per_thr * total_thr;
    uint64_t stride_idx = total_thr;

    if (start_idx > nsize) {
        start_idx = nsize;
    }

    if (end_idx > nsize) {
        end_idx = nsize;
    }

    double alpha = 0.5;
    uint64_t i, j;
    for (j = 0; j < ntrials; ++j) {
        for (i = start_idx; i < end_idx; i += stride_idx) {
            double beta = 0.8;

	    //#if (ERT_FLOP & 2) == 2       /* add 2 flops */
            KERNEL2(beta, A[i], alpha);

            A[i] = beta;
        }
        alpha = alpha * (1 - 1e-8);
    }
}

void gpuKernel_triad(uint64_t nsize, uint64_t ntrials, double *__restrict__ A,
                int *bytes_per_elem, int *mem_accesses_per_elem) {
    *bytes_per_elem = sizeof(*A);
    *mem_accesses_per_elem = 2;
    flop = 2;
    // gpu_blocks = (nsize+1023)/1024;
    block_stride_triad<<<gpu_blocks, gpu_threads>>>(ntrials, nsize, A);
}

void gpuKernel(uint64_t nsize, uint64_t ntrials, double *__restrict__ A,
               int *bytes_per_elem, int *mem_accesses_per_elem) {
    *bytes_per_elem = sizeof(*A);
    *mem_accesses_per_elem = 2;
    // gpu_blocks = (nsize+1023)/1024;
    block_stride<<<gpu_blocks, gpu_threads>>>(ntrials, nsize, A);
}

double getTime() {
    double time;
    struct timeval tm;
    gettimeofday(&tm, NULL);
    time = tm.tv_sec + (tm.tv_usec / 1000000.0);
    return time;
}

int main(int argc, char *argv[]) {

    key_t shmkey, shmkey1; /*      shared memory key       */
    int shmid, shmid1;     /*      shared memory id        */

    int *p_gpu, *p_cpu; /*      shared variable         */ /*shared */
    // shmdt (p);shmctl (shmid, IPC_RMID, 0);exit(0);

    /* initialize a shared variable in shared memory */
    // shmkey = ftok ("/home/66m", 5);       /* valid directory name and a
    // number */
    shmkey = ftok("/dev/null", 5);  /* valid directory name and a number */
    shmkey1 = ftok("/dev/null", 6); /* valid directory name and a number */
    // printf ("shmkey for p = %d\n", shmkey);

    shmid = shmget(shmkey, sizeof(int), 0644 | IPC_CREAT);
    shmid1 = shmget(shmkey1, sizeof(int), 0644 | IPC_CREAT);
    if (shmid < 0) { /* shared memory error check */
        perror("shmget\n");
        exit(1);
    }
    // pthread_mutex_t *m;
    // Mutex a(m,false);
    p_gpu = (int *)shmat(shmid, NULL, 0);  /* attach p to shared memory */
    p_cpu = (int *)shmat(shmid1, NULL, 0); /* attach p to shared memory */
    //printf("p_cpu=%d  p_gpu=%d is allocated in shared memory.\n\n", *p_cpu,*p_gpu);
    *p_gpu = 20;                            //*p = 0;
    if (*p_cpu != 20 && *p_cpu != 1) *p_cpu = -5;                           //*p = 0;

    //if (*p_cpu != 20) *p_cpu = -5;                           //*p = 0;
    //printf("p_cpu=%d  p_gpu=%d is allocated in shared memory.\n\n", *p_cpu,
           //*p_gpu);

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

    {
        id = 0;
        nthreads = 1;

        int num_gpus = 0;
        int gpu;
        int gpu_id;
        int numSMs;

        cudaGetDeviceCount(&num_gpus);
        if (num_gpus < 1) {
            fprintf(stderr, "No CUDA device detected.\n");
            return -1;
        }

        for (gpu = 0; gpu < num_gpus; gpu++) {
            cudaDeviceProp dprop;
            cudaGetDeviceProperties(&dprop, gpu);
            /* printf("%d: %s\n",gpu,dprop.name); */
        }

        cudaSetDevice(id % num_gpus);
        cudaGetDevice(&gpu_id);
        cudaDeviceGetAttribute(&numSMs, cudaDevAttrMultiProcessorCount, gpu_id);

        void (*fun_ptr)(uint64_t, uint64_t, double *, int *, int *);
        double *d_buf;
        for (int ar = 2; ar <= argc; ar++) {

            sleep(5);

            // if (id == 0) printf("Current kernel:  %s\n", argv[ar-1]);
            if (strcmp(argv[ar - 1], "1") == 0)
                fun_ptr = &gpuKernel1;
            if (strcmp(argv[ar - 1], "2") == 0)
                fun_ptr = &gpuKernel2;
            if (strcmp(argv[ar - 1], "3") == 0)
                fun_ptr = &gpuKernel3;
            if (strcmp(argv[ar - 1], "4") == 0)
                fun_ptr = &gpuKernel4;
            if (strcmp(argv[ar - 1], "5") == 0)
                fun_ptr = &gpuKernel5;
            if (strcmp(argv[ar - 1], "6") == 0)
                fun_ptr = &gpuKernel_triad;


            uint64_t nsize = PSIZE / nthreads;
            nsize = nsize & (~(64 - 1));
            nsize = nsize / sizeof(double);
            uint64_t nid = nsize * id;

            // initialize small chunck of buffer within each thread
            initialize(nsize, &buf[nid], 1.0);

            cudaMalloc((void **)&d_buf, nsize * sizeof(double));
            cudaMemset(d_buf, 0, nsize * sizeof(double));
            cudaDeviceSynchronize();

            double startTime, endTime;
            uint64_t n;
            uint64_t t;
            int bytes_per_elem;
            int mem_accesses_per_elem;
            double seconds = 0;
            uint64_t working_set_size = 0;
            uint64_t total_bytes = 0;
            uint64_t total_flops = 0;

            n = 1 << 22;
            n = n * 8;

            // int lim = 35;
            int lim;
#ifdef LIM
            lim = LIM;
#endif
            while (n <= nsize) { // working set - nsize

                uint64_t ntrials = nsize / n;
                if (ntrials < 1)
                    ntrials = 1;

                // warmup begins
                /*
                cudaMemcpy(d_buf, &buf[nid], n*sizeof(double),
                cudaMemcpyHostToDevice); cudaDeviceSynchronize(); for (t = 1; t
                <= 30; t = t + 1) { gpuKernel(n, t, d_buf, &bytes_per_elem,
                &mem_accesses_per_elem); cudaDeviceSynchronize();

                }
                cudaMemcpy(&buf[nid], d_buf, n*sizeof(double),
                cudaMemcpyDeviceToHost); cudaDeviceSynchronize();
                */
                // warmup ends

                for (t = lim - 35; t <= lim;
                     t = t + 1) { // working set - ntrials
                    cudaMemcpy(d_buf, &buf[nid], n * sizeof(double),
                               cudaMemcpyHostToDevice);
                    cudaDeviceSynchronize();

                    if (t >= (lim - 19)) {
                        *p_gpu = 10;
                        while (1) {
                            if (*p_cpu == 10 || *p_cpu == 1 || *p_cpu == 33 || *p_cpu == -5)
                                break;
                            fprintf(stderr, "p_cpu=%d  p_gpu=%d is allocated in shared "
                                   "memory.\n",*p_cpu, *p_gpu);

                            //(*fun_ptr)(1000, t, &buf[nid], &bytes_per_elem,
                            //&mem_accesses_per_elem);
                            //(*fun_ptr)(10000, t, d_buf, &bytes_per_elem,
                            //&mem_accesses_per_elem); cudaDeviceSynchronize();
                        }

                        *p_gpu = 1;
                    }

                    if ((id == 0) && (rank == 0)) {
                        startTime = getTime();
                    }

                    (*fun_ptr)(n, t, d_buf, &bytes_per_elem,
                               &mem_accesses_per_elem);

                    cudaDeviceSynchronize();

                    if ((id == 0) && (rank == 0) && (t > (lim - 20))) {
                        // if ((id == 0) && (rank == 0)) {
                        // if ((id == 0) && (rank == 0) && (t > 580)) {
                        endTime = getTime();
                        seconds += (double)(endTime - startTime);
                        working_set_size = n * nthreads * nprocs;
                        total_bytes += t * working_set_size * bytes_per_elem *
                                       mem_accesses_per_elem;
                        total_flops += t * working_set_size * flop;
                        // std::cout << "nthreads: " << nthreads << " value of
                        // n: "
                        // << n << " working set size: " << working_set_size <<
                        // "total bytes: " << total_bytes << " total_flops: " <<
                        // total_flops << std::endl;
                        // total_flops += t * working_set_size * ERT_FLOP;
                    }

                    if ((id == 0) && (rank == 0) && (t == lim)) {
                        // if ((id == 0) && (rank == 0) && (t == 600)) {

                        printf("BadnWindth : %15.3lf\n", total_bytes * 1.0 /
                                                             seconds / 1024 /
                                                             1024 / 1024);
                        printf("Total Bytes: %15" PRIu64 "\n", total_bytes);
                        printf("Total flops: %15" PRIu64 "\n", total_flops);
                        printf("Total time : %15.6lf \n", seconds);

                    } // print

                    if (id == 0)
                        *p_gpu = 0;

                    cudaMemcpy(&buf[nid], d_buf, n * sizeof(double),
                               cudaMemcpyDeviceToHost);
                    cudaDeviceSynchronize();
                }
	            if (id == 0)
                        *p_gpu = 0;


                n = nsize + 1;

                seconds = 0;
                working_set_size = 0;
                total_bytes = 0;
                total_flops = 0;

                /* while(1){
                            gpuKernel1(n/8, t, d_buf, &bytes_per_elem,
                               &mem_accesses_per_elem);
                            cudaDeviceSynchronize();
                            printf ("p=%d is allocated in shared memory.\n\n",
                   *p);


                        } */

                // if(*p_gpu == 1) break;

                /*	nNew = 1.1 * n;
            if (nNew == n) {
                    nNew = n+1;
            }

            n = nNew; */

            } // working set - nsize
        }     // argc

        cudaFree(d_buf);

        if (cudaGetLastError() != cudaSuccess) {
            printf("Last cuda error: %s\n",
                   cudaGetErrorString(cudaGetLastError()));
        }

        cudaDeviceReset();
    } // parallel region

    *p_gpu = 33;
    free(buf);

    return 0;
}
