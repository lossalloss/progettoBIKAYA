
#Salvo le directory dei file che mi servono nelle rispettive variabili
directory_crtso = /usr/include/uarm/crtso.o
directory_libuarm = /usr/include/uarm/libuarm.o
dir_elf32ltsarm = /usr/include/uarm/ldscripts/elf32ltsarm.h.uarmcore.x

#creo il file terminal.o utilizzando terminal.c
terminal.o: terminal.c
	arm-none-eabi-gcc -mcpu=arm7tdmi -c -o terminal.o terminal.c

#creo il file finale output utilizzando helloworld.o e le varabili di prima
#$("nomevariabie") indica che sto utilizzando la variabile "nomevariabile"
kernel: terminal.o 
	arm-none-eabi-ld -T $(dir_elf32ltsarm) -o kernel $(directory_crtso) $(directory_libuarm) terminal.o
