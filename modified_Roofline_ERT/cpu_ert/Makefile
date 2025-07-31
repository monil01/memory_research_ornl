CC = g++
#CFLAGS = -O3 -fopenmp -DBW_PCT=${pct} -DINFIN_LOOP=${inf}
#CFLAGS = -O3 -fopenmp -DINTENS=${intens} -DINFIN_LOOP=${inf} -DLIM=${lim}
CFLAGS = -O3 -fopenmp -DLIM=${lim} -DINFIN_LOOP=${inf} 
#CFLAGS = -O3 -fopenmp -DINFIN_LOOP=${inf} -DLIM=${lim} -DINTENS=${intens}


all: driver 
#all: stream_f.exe stream_c.exe


driver: driver1.c
	$(CC) $(CFLAGS) driver1.c -o cpu_ert 

clean:
	rm -f driver cpu_ert *.o
