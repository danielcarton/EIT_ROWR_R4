#include <print.h>
#include <stdio.h>

//------------------------------------------------------------------------

static int print_callback(char c, FILE* file);
static FILE avr_stdout = FDEV_SETUP_STREAM(print_callback, NULL, _FDEV_SETUP_WRITE);

//------------------------------------------------------------------------

void print_init() {
  PORTA.DIRSET = 1 << 0;
  PORTA.DIRCLR = 1 << 1;

  USART0.CTRLB = USART_TXEN_bm | USART_RXEN_bm;
  USART0.BAUD  = 4 * F_CPU / 230400;

  stdout = &avr_stdout;
}

//------------------------------------------------------------------------

static void print_char(char c) {
  while ((USART0.STATUS & USART_DREIF_bm) == 0);
  USART0.TXDATAL = c;
}

//------------------------------------------------------------------------

static int print_callback(char c, FILE* file) {
  // Some terminals does not translate LF to CRLF
  if (c == '\n') 
    print_char('\r');
    
  print_char(c);
  return 0;
}
