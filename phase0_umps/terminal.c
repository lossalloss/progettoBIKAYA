#include "umps/arch.h"
#include "umps/types.h"

#define ST_READY           1
#define ST_BUSY            3
#define ST_TRANSMITTED     5
#define ST_RECEIVED        5

#define CMD_ACK            1
#define CMD_TRANSMIT       2
#define CMD_RECV           2

#define CHAR_OFFSET        8
#define TERM_STATUS_MASK   0xFF

#define P_READY            1
#define P_BUSY             3

#define CMD_PRINTCHR       2



volatile termreg_t *terminal = (termreg_t*) DEV_REG_ADDR(IL_TERMINAL, 0);
volatile dtpreg_t *printer = (dtpreg_t*) DEV_REG_ADDR(IL_PRINTER, 0);

static unsigned int rx_status(volatile termreg_t *tp);
static unsigned int pr_status(volatile dtpreg_t *tp);

int print_putchar(char c);

int term_getchar(void);

void main(void){
	
	while (term_getchar() != '\n')
		;

	WAIT();
}

int print_putchar(char c){

	unsigned int stat;
	
	stat = pr_status(printer);
	if (stat != P_READY)
		return -1;

	printer->data0 = c;
	printer->command = CMD_PRINTCHR;
	
	while ((stat = pr_status(printer)) == P_BUSY)
		;
	
	if (stat != P_READY)
		return -1;
	
	printer->command = CMD_ACK;

	return 0;
}



int term_getchar(void)
{
    unsigned int stat;

    stat = rx_status(terminal);
    if (stat != ST_READY && stat != ST_RECEIVED)
        return -1;

    terminal->recv_command = CMD_RECV;
    

    while ((stat = rx_status(terminal)) == ST_BUSY)
        ;

    if (stat != ST_RECEIVED)
        return -1;

    stat = terminal->recv_status;
    
    print_putchar(stat >> CHAR_OFFSET);

    terminal->recv_command = CMD_ACK;

    return stat >> CHAR_OFFSET;
}

static unsigned int rx_status(volatile termreg_t *tp)
{
    return ((tp->recv_status) & TERM_STATUS_MASK);
}
static unsigned int pr_status(volatile dtpreg_t *tp)
{
    return (tp->status);
}
