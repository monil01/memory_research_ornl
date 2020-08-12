GCC=g++
PAPILD=-lpapi
PAPILDPATH=-L/home/mmonil/packages/download_tar/papi/src/install_pw/lib
PAPIINCLUDE=-I/home/mmonil/packages/download_tar/papi/src/install_pw/include

#all: vecmul
all: vecmul papi nat_papi tau omp

vecmul: vecmul.c
	${GCC} vecmul.c -o serial_vecmul

papi_ex: PAPI_add_remove_event.c
	${GCC} ${PAPIINCLUDE} ${PAPILDPATH} PAPI_add_remove_event.c -o  papi_add_remove ${PAPILD}
	#${GCC} ${PAPIINCLUDE} PAPI_add_remove_event.c -o  papi_add_remove ${PAPILD}

papi: vecmul_PAPI.c
	${GCC} ${PAPIINCLUDE} ${PAPILDPATH} vecmul_PAPI.c -o vecmul_PAPI ${PAPILD}

nat_papi: vecmul_NAT_PAPI.c
	${GCC} ${PAPIINCLUDE} ${PAPILDPATH} vecmul_NAT_PAPI.c -o vecmul_NAT_PAPI ${PAPILD}



tau: vecmul.c
	tau_cxx.sh -optCompInst vecmul.c -o tau_vecmul

omp: vecmul_openmp.c
	tau_cxx.sh -optCompInst vecmul_openmp.c -o omp_vecmul -fopenmp



clean:
	rm serial_vecmul papi_add_remove vecmul_PAPI tau_vecmul omp_vecmul profile.0.0* *.o; rm -rf MULT*
