CC =icc -qopenmp
OPTI =-O3
OBJ =driver.o kernel.o rdtsc.o
CFLAGS =  -xHost -Wall -g
LDFLAGS =-lm
EXE=prog
#-qopt-report=5 -qopt-report-phase=vec
all:		$(EXE)
$(EXE):		$(OBJ)
	$(CC) -o $@ $^ -lm 

kernel.o: 	kernel.c
	$(CC) $(OPTI) $(CFLAGS) -c $< -o $@
driver.o:	driver.c
	$(CC) -c $< -o $@ $(CFLAGS)
rdtsc.o:	rdtsc.c
	$(CC) -c $< -o $@ $(CFLAGS)
clean:
	rm -rf *.o
mrproper: clean
	rm -f prog*
