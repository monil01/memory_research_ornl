GCC=gcc
ICC=icpc
PAPILD=-lpapi
#ICCFLAG=-qopt-streaming-stores always
#ICCFLAG=-qopt-streaming-stores=never
ICCFLAG=-qopt-streaming-stores=auto
PAPILDPATH=-L/home/mmonil/packages/download_tar/papi/src/install/lib
PAPIINCLUDE=-I/home/mmonil/packages/download_tar/papi/src/install/include
PAPILDPATH_PW=-L/home/mmonil/packages/download_tar/papi_pw/src/install/lib
PAPIINCLUDE_PW=-I/home/mmonil/packages/download_tar/papi_pw/src/install/include

#all: omp
#all: papi
all: nat_papi 
#all: papi_pw 
#all: vecmul papi nat_papi papi_pw tau omp

vecmul: vecmul.c
	${GCC} vecmul.c -o serial_vecmul

papi_ex: PAPI_add_remove_event.c
	${GCC} ${PAPIINCLUDE} ${PAPILDPATH} PAPI_add_remove_event.c -o  papi_add_remove ${PAPILD}
	#${GCC} ${PAPIINCLUDE} PAPI_add_remove_event.c -o  papi_add_remove ${PAPILD}

papi: vecmul_PAPI.c
	${GCC} ${PAPIINCLUDE} ${PAPILDPATH} vecmul_PAPI.c -o vecmul_PAPI ${PAPILD}

papi_pw: vecmul_PAPI_pw.c
	${GCC} ${PAPIINCLUDE_PW} ${PAPILDPATH_PW} vecmul_PAPI_pw.c -o vecmul_PAPI_pw ${PAPILD}

nat_papi: vecmul_NAT_PAPI.c
	#${GCC} ${PAPIINCLUDE} ${PAPILDPATH} vecmul_NAT_PAPI.c -o vecmul_NAT_PAPI ${PAPILD}
	${ICC} ${PAPIINCLUDE} ${PAPILDPATH} ${ICCFLAG} vecmul_NAT_PAPI.c -o vecmul_NAT_PAPI ${PAPILD}

jacobi: jacobi.c
	tau_cxx.sh -optCompInst jacobi.c -o tau_vecmul -fopenmp

tau: vecmul.c
	#tau_cxx.sh -optCompInst -qopt-streaming-stores=always vecmul.c -o tau_vecmul
	tau_cxx.sh -optCompInst  vecmul.c -o tau_vecmul

omp: vecmul_openmp.c
	tau_cxx.sh -optCompInst vecmul_openmp.c -o omp_vecmul -fopenmp



clean:
	rm serial_vecmul papi_add_remove vecmul_PAPI tau_vecmul omp_vecmul profile.0.0* *.o; rm -rf MULT*
