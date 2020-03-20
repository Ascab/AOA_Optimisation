CC =gcc
OBJ =driver.o kernel.o rdtsc.o
OPTI =-O2
CFLAGS =-Wall -g
LDFLAGS =-lm

all:		prog
prog:		driver.o kernel.o rdtsc.o
	$(CC) -o $@ $^ -lm

kernel.o: 	kernel.c
	$(CC) $(CFLAGS) $(OPTI) -lm -c $< -o $@
driver.o:	driver.c
	$(CC) $(CFLAGS) -c $< -o $@
rdtsc.o:	rdtsc.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -rf $(OBJ)
mrproper: clean
	rm -f prog
