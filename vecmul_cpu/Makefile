GCC=g++
PAPILD=-lpapi
#PAPILD=/home/users/mmonil/ORNL_seyong/profile_programs/papi/papi/src/libpapi.a
#PAPIINCLUDE=-I/home/users/mmonil/ORNL_seyong/profile_programs/papi/papi/src

all: vecmul papi_ex papi tau omp

vecmul: vecmul.c
	${GCC} vecmul.c -o serial_vecmul

papi_ex: PAPI_add_remove_event.c
	${GCC} ${PAPIINCLUDE} PAPI_add_remove_event.c -o  papi_add_remove ${PAPILD}
	#${GCC} ${PAPIINCLUDE} PAPI_add_remove_event.c -o  papi_add_remove ${PAPILD}

papi: vecmul_PAPI.c
	${GCC} vecmul_PAPI.c -o vecmul_PAPI ${PAPILD}


tau: vecmul.c
	tau_cxx.sh -optCompInst vecmul.c -o tau_vecmul

omp: vecmul_openmp.c
	tau_cxx.sh -optCompInst vecmul_openmp.c -o omp_vecmul -fopenmp



clean:
	rm serial_vecmul papi_add_remove vecmul_PAPI tau_vecmul omp_vecmul profile.0.0*; rm -rf MULT*
