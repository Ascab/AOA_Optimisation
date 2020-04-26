CC =gcc
OPTI =-O3
OBJ =driver.o kernel.o rdtsc.o
CFLAGS =-Wall -g
LDFLAGS =-lm
EXE=prog
L3=-DN_WARMUP=15 -DN_MESURES=10 -DN_REPET=31 -DTAILLE_TAB=500000
RAM=-DN_WARMUP=15 -DN_MESURES=10 -DN_REPET=31 -DTAILLE_TAB=1500000
ifeq ($(CC),icc)
	BOOST=-xHost -qopenmp
else
	BOOST=-march=native -fopenmp
endif

all:		$(EXE)
$(EXE):		$(OBJ)
	$(CC) -o $@ $^ -lm

kernel.o: 	kernel.c
	$(CC) $(OPTI) $(CFLAGS) -c $< -o $@
driver.o:	driver.c
	$(CC) -c $< -o $@ $(CFLAGS) -O2 -lm $($(CACHE)) -D$(DEFINE)=1
rdtsc.o:	rdtsc.c
	$(CC) -c $< -o $@ $(CFLAGS) -O2
common.o:	common.c
	$(CC) -c $< -o $@ $(CFLAGS) -O2

clean:
	rm -rf *.o
mrproper: clean
	rm -f prog*
%-O2: kernel.c driver.o rdtsc.o common.o
	$(CC) -O2 $^ -o prog -lm
%-O3: kernel.c driver.o rdtsc.o common.o
	$(CC) -O3 $^ -o prog -lm
%-O3+: kernel.c driver.o rdtsc.o common.o
	$(CC) -O3 $^ -o prog -lm $(BOOST)
%-O3+-unroll: kernel.c driver.o rdtsc.o common.o
	$(CC) -O3 $^ -o prog -lm $(BOOST) -funroll-loops
%-O3+-fast-math: kernel.c driver.o rdtsc.o common.o
	$(CC) -O3 $^ -o prog -lm $(BOOST) -ffast-math
%-O3-total: kernel.c driver.o rdtsc.o common.o
	$(CC) -O3 $^ -o prog -lm $(BOOST) -funroll-loops -ffast-math

%-Ofast: kernel.c driver.o rdtsc.o common.o
	$(CC) -Ofast $^ -o prog -lm

%-vect_hoist_interchange_mem: kernel.c driver.o rdtsc.o common.o
	$(CC) -O3 $^ -o prog -lm $(BOOST) -D$(DEFINE)=1
%-vect_hoist_interchange: kernel.c driver.o rdtsc.o common.o
	$(CC) -O3 $^ -o prog -lm $(BOOST) -D$(DEFINE)=1
%-vect: kernel.c driver.o rdtsc.o common.o
	$(CC) -O3 $^ -o prog -lm $(BOOST) -D$(DEFINE)=1
%-baseline : kernel.c driver.o rdtsc.o common.o
	$(CC) -O3 $^ -o prog -lm $(BOOST) -D$(DEFINE)=1
%-vect_hoist_interchange_parallel : kernel.c driver.o rdtsc.o common.o
	$(CC) -O3 $^ -o prog -lm $(BOOST) -D$(DEFINE)=1 -DPARALLEL=1
%-vect_hoist_interchange_mem_parallel : kernel.c driver.o rdtsc.o common.o
	$(CC) -O3 $^ -o prog -lm $(BOOST) -D$(DEFINE)=1 -DPARALLEL = 1
