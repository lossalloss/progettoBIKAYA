#include "/usr/include/uarm/libuarm.h"

char *error="If this got printed something fishy has happened..\n\0";

int main(){

	while (term_getchar() != '\n')

	;

	WAIT();
}



    tprint("Hello World!\n\0");

    HALT();

    tprint(error);

    return 0;
}
