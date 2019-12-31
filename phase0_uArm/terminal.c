/* ------------------------------------------------------------------------------------------------
| Busi Samuele
| Sallei Enrico
| Raimondi Bianca
| Amato Alessio 
| Nota: funzione term_getchar from: https://github.com/tjonjic/umps.git examples/termio/terminal.c
 -------------------------------------------------------------------------------------------------*/
#include "termprint.h"
#include "system.h"

#define DEV_S_READY   1  
#define DEV_PRNT_C_PRINTCHR 2 
#define DEV_C_ACK   1 
#define DEV_TRCV_C_RECVCHAR 2   
#define DEV_TRCV_S_RECVERR  4  
#define DEV_TRCV_S_CHARRECV 5
#define DEV_PRNT_S_BUSY    2
#define DEV_TRCV_S_BUSY    3
#define DEV_PRNT_C_RESET   0
#define CHAR_OFFSET        8
#define TERM_STATUS_MASK   0xFF

volatile termreg_t *terminal = (termreg_t*) DEV_REG_ADDR(IL_TERMINAL, 0); /* Device: Terminal 0 */
volatile dtpreg_t *printer = (dtpreg_t*) DEV_REG_ADDR(IL_PRINTER, 0);     /* Device: Printer 0 */

int term_getchar(void); /* read char from terminal */
int print_putchar(char c); /* print char in printer 0 */
static unsigned int rx_status(volatile termreg_t *tp); /* Get status from RECVSTATUS.RECVD-CHAR. using bitwise AND and 8 bit offset */

static unsigned int rx_status(volatile termreg_t *tp){
    return ((tp->recv_status) & TERM_STATUS_MASK);
}

int term_getchar(void){
    unsigned int stat;

    stat = rx_status(terminal);
    if (stat != DEV_S_READY && stat != DEV_TRCV_S_CHARRECV){ /* terminal ready and ack received */
        return -1;
	}
        terminal->recv_command = DEV_TRCV_C_RECVCHAR;

    while ((stat = rx_status(terminal)) == DEV_TRCV_S_BUSY) /* wait for terminal to complete receive */
        ;

    if (stat != DEV_TRCV_S_CHARRECV){
        return -1;
	}
        stat = terminal->recv_status;

    print_putchar(stat >> CHAR_OFFSET); /* bitwise rightshift to output char, call print_putchar(char) */
    terminal->recv_command = DEV_C_ACK; /* after successful read and print send acknowledgment */

    return stat >> CHAR_OFFSET;
}

int print_putchar(char c){

    if(printer->status != DEV_S_READY) return -1; /* printer ready */

        printer->data0 = c;
	    printer->command = DEV_PRNT_C_PRINTCHR;

    while (printer->status == DEV_PRNT_S_BUSY) /* wait for printer to complete print */
        ;

    if(printer->status != DEV_S_READY) return -1; 
	
	    printer->command = DEV_C_ACK; /* send ackacknowledgment */
	return 0;
}

int main(){
	
	while (term_getchar() != '\n') /* read and print until end of line */
		;

    HALT(); /* request BIOS Halt service */
    return 0;
}
