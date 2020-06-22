make clean
make

export TAU_METRICS=PAPI_L3_TCA:PAPI_L3_TCM:PAPI_L3_TCR:PAPI_L3_TCW:TIME
./tau_vecmul
#./omp_vecmul

export TAU_METRICS=PAPI_L3_DCA:PAPI_L3_DCR:PAPI_L3_DCW:TIME
./tau_vecmul
#./omp_vecmul

export TAU_METRICS=PAPI_L3_ICA:PAPI_L3_ICR:PAPI_L3_LDM:TIME
./tau_vecmul
#./omp_vecmul

ls

cd MULTI__PAPI_L3_TCA
pprof
cd ..

cd MULTI__PAPI_L3_TCM
pprof
cd ..

cd MULTI__PAPI_L3_TCR
pprof
cd ..

cd MULTI__PAPI_L3_TCW
pprof
cd ..

cd MULTI__PAPI_L3_DCA
pprof
cd ..

cd MULTI__PAPI_L3_DCR
pprof
cd ..

cd MULTI__PAPI_L3_DCW
pprof
cd ..

cd MULTI__PAPI_L3_ICA
pprof
cd ..

cd MULTI__PAPI_L3_ICR
pprof
cd ..

cd MULTI__PAPI_L3_LDM
pprof
cd ..

echo " data for each counters"
echo " " 

cd MULTI__PAPI_L3_DCA
pprof | grep -i "vecmul("
cd ..

cd MULTI__PAPI_L3_DCR
pprof | grep -i "vecmul("
cd ..

cd MULTI__PAPI_L3_DCW
pprof | grep -i "vecmul("
cd ..

cd MULTI__PAPI_L3_ICA
pprof | grep -i "vecmul("
cd ..

cd MULTI__PAPI_L3_ICR
pprof | grep -i "vecmul("
cd ..

cd MULTI__PAPI_L3_LDM
pprof | grep -i "vecmul("
cd ..

cd MULTI__PAPI_L3_TCA
pprof | grep -i "vecmul("
cd ..

cd MULTI__PAPI_L3_TCM
pprof | grep -i "vecmul("
cd ..

cd MULTI__PAPI_L3_TCR
pprof | grep -i "vecmul("
cd ..

cd MULTI__PAPI_L3_TCW
pprof | grep -i "vecmul("
cd ..
