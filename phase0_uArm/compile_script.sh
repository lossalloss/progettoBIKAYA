#!/bin/sh

rm -f *.o kernel kernel.*.umps

mipsel-linux-gnu-gcc -ansi -mips1 -mfp32 -I /usr/local/include/umps2 -c terminal.c;

mipsel-linux-gnu-ld -o kernel terminal.o /usr/local/lib/umps2/crtso.o /usr/local/lib/umps2/libumps.o -nostdlib -T /usr/local/share/umps2/umpscore.ldscript;

umps2-elf2umps -k kernel;

