#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>
#include <stdio.h>

//------------------------------------------------------------------------

static int print_callback(char c, FILE* file);
static FILE avr_stdout = FDEV_SETUP_STREAM(print_callback, NULL, _FDEV_SETUP_WRITE);

//------------------------------------------------------------------------

static void print_init() {
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
  if (c == '\n') 
    print_char('\r');
    
  print_char(c);
  return 0;
}

//------------------------------------------------------------------------

static void system_init() {
  // Set CPU frequency to 24 MHz
  ccp_write_io((u8* )&CLKCTRL.MCLKCTRLB, 0);
  ccp_write_io((u8* )&CLKCTRL.OSCHFCTRLA, CLKCTRL_FRQSEL_24M_gc);
  ccp_write_io((u8* )&WDT.CTRLA, 0);
}

int main() {
  print_init();
  printf("Testing: %d\n", 234);
  return 0;
}
