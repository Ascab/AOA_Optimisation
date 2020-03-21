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
    #L1
    maqao oneview --create-report=one binary=$i run_command="<binary> 10 50 1000 2000" --xp=maqao_L1_$i
    firefox maqao_L1_$i/RESULTS/*_one_html/index.html&
    #L2
    maqao oneview --create-report=one binary=$i run_command="<binary> 10 50 1000 147456" --xp=maqao_L2_$i
    firefox maqao_L2_$i/RESULTS/*_one_html/index.html&
    #L3
    maqao oneview --create-report=one binary=$i run_command="<binary> 10 50 1000 500000" --xp=maqao_L3_$i
    firefox maqao_L3_$i/RESULTS/*_one_html/index.html&
    #RAM
    maqao oneview --create-report=one binary=$i run_command="<binary> 10 50 1000 600000" --xp=maqao_RAM_$i
    firefox maqao_RAM_$i/RESULTS/*_one_html/index.html&
done
