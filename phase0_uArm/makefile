
#Salvo le directory dei file che mi servono nelle rispettive variabili
directory_crtso = /usr/local/include/uarm/crtso.o
directory_libuarm = /usr/local/include/uarm/libuarm.o
dir_elf32ltsarm = /usr/local/include/uarm/ldscripts/elf32ltsarm.h.uarmcore.x

#creo il file finale output utilizzando helloworld.o e le varabili di prima
#$("nomevariabie") indica che sto utilizzando la variabile "nomevariabile"
output: helloworld.o 
	arm-none-eabi-ld -T $(dir_elf32ltsarm) -o output $(directory_crtso) $(directory_libuarm) helloworld.o

#creo il file helloworld.o utilizzando helloworld.c
helloworld.o: helloworld.c
	arm-none-eabi-gcc -mcpu=arm7tdmi -c -o helloworld.o helloworld.c

