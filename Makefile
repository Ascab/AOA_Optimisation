CC =gcc
OPTI =-O3
OBJ =driver.o kernel.o rdtsc.o
CFLAGS =-Wall -g
LDFLAGS =-lm
EXE=prog

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
