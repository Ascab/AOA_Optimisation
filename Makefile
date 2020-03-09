$CC =gcc
$OBJ =driver.o kernel.o rdtsc.o
$OPTI =-O3
$CFLAGS =-Wall
$LDFLAGS =-lm

all:		prog
prog:		driver.o kernel.o rdtsc.o
	$(CC) -o $@ $^ -lm

kernel.o: 	kernel.c
	$(CC) $(OPTI) -lm -c $< -o $@
driver.o:	driver.c
	$(CC) -c $< -o $@
rdtsc.o:	rdtsc.c
	$(CC) -c $< -o $@
clean:
	rm -rf $(OBJS)
mrproper: clean
	rm -f prog
