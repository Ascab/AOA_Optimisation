#!/bin/bash
make mrproper
make all CC=gcc OPTI=-O2 EXE=prog_gcc_O2
rm kernel.o
make all CC=gcc OPTI=-O3 EXE=prog_gcc_03
rm kernel.o
make all CC=gcc OPTI=-"O3 -march=native" EXE=prog_gcc_O3_march=native
rm kernel.o
make all CC=icc OPTI=-O2 EXE=prog_icc_O2
rm kernel.o
make all CC=icc OPTI=-O3 EXE=prog_icc_O3
rm kernel.o
make all CC=icc OPTI="-xHost -O3" EXE=prog_icc_O3_xHost
rm kernel.o
for i in prog*
do
    maqao oneview --create-report=one binary=$i run_command="<binary> 300 100 30" --xp=maqao_$i
done
