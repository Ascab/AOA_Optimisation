CC =gcc
OPTI =-O3
OBJ =driver.o kernel.o rdtsc.o
CFLAGS =-Wall -g
LDFLAGS =-lm
EXE=prog
L1=-DN_WARMUP=10 -DN_MESURES=1000 -DN_REPET=31 -DTAILLE_TAB=2000
L2=-DN_WARMUP=15 -DN_MESURES=100 -DN_REPET=31 -DTAILLE_TAB=20000
ifeq ($(CC),icc)
	BOOST=-xHost
else
	BOOST=-march=native
endif

all:		$(EXE)
$(EXE):		$(OBJ)
	$(CC) -o $@ $^ -lm

kernel.o: 	kernel.c
	$(CC) $(OPTI) $(CFLAGS) -c $< -o $@
driver.o:	driver.c
	$(CC) -c $< -o $@ $(CFLAGS) -O2 -lm $($(CACHE))
rdtsc.o:	rdtsc.c
	$(CC) -c $< -o $@ $(CFLAGS) -O2
common.o:	common.c
	$(CC) -c $< -o $@ $(CFLAGS) -O2

clean:
	rm -rf *.o
mrproper: clean
	rm -f prog*

%-O2: kernel.c driver.o rdtsc.o common.o
	$(CC) $(CFLAGS) -O2 $^ -o prog -lm
%-O3: kernel.c driver.o rdtsc.o common.o
	$(CC) $(CFLAGS) -O3 $^ -o prog -lm
%-O3+: kernel.c driver.o rdtsc.o common.o
	$(CC) $(CFLAGS) -O3 $^ -o prog -lm $(BOOST)
%-O3+-unroll: kernel.c driver.o rdtsc.o common.o
	$(CC) $(CFLAGS) -O3 $^ -o prog -lm $(BOOST) -funroll-loops
%-O3+-fast-math: kernel.c driver.o rdtsc.o common.o
	$(CC) $(CFLAGS) -O3 $^ -o prog -lm $(BOOST) -ffast-math
%-O3-total: kernel.c driver.o rdtsc.o common.o
	$(CC) $(CFLAGS) -O3 $^ -o prog -lm $(BOOST) -funroll-loops -ffast-math
%-Ofast: kernel.c driver.o rdtsc.o common.o
	$(CC) $(CFLAGS) -Ofast $^ -o prog -lm
	
%-Phase2-std: kernel.c driver.o rdtsc.o common.o
	$(CC) $(CFLAGS) -O3 $^ -o prog -lm
%-Phase2-simple-cond: kernel.c driver.o rdtsc.o common.o
	$(CC) $(CFLAGS) -O3 $^ -o prog -lm -DSIMPLECOND=1
%-Phase2-loop-swap: kernel.c driver.o rdtsc.o common.o
	$(CC) $(CFLAGS) -O3 $^ -o prog -lm -DBASELINE=1
%-Phase2-unroll: kernel.c driver.o rdtsc.o common.o
	$(CC) $(CFLAGS) -O3 $^ -o prog -lm -DBASELINE=2
%-Phase2-total: kernel.c driver.o rdtsc.o common.o
	$(CC) $(CFLAGS) -O3 $^ -o prog -lm -DBASELINE=2 -DSIMPLECOND=1
%-Phase2-parallel-6: kernel.c driver.o rdtsc.o common.o
	$(CC) $(CFLAGS) -O3 $^ -o prog -lm -fopenmp -DTHREADS=6
%-Phase2-simple-cond-parallel-6: kernel.c driver.o rdtsc.o common.o
	$(CC) $(CFLAGS) -O3 $^ -o prog -lm -DSIMPLECOND=1 -fopenmp -DTHREADS=6
%-Phase2-loop-swap-parallel-6: kernel.c driver.o rdtsc.o common.o
	$(CC) $(CFLAGS) -O3 $^ -o prog -lm -DBASELINE=1 -fopenmp -DTHREADS=6
%-Phase2-unroll-parallel-6: kernel.c driver.o rdtsc.o common.o
	$(CC) $(CFLAGS) -O3 $^ -o prog -lm -DBASELINE=2 -fopenmp -DTHREADS=6
%-Phase2-total-parallel-6: kernel.c driver.o rdtsc.o common.o
	$(CC) $(CFLAGS) -O3 $^ -o prog -lm -DBASELINE=2 -DSIMPLECOND=1 -fopenmp -DTHREADS=6
