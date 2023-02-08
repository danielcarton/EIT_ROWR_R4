#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>
#include <stdio.h>

//------------------------------------------------------------------------

static int printf_hook(char c, FILE* file);
static FILE avr_stdout = FDEV_SETUP_STREAM(printf_hook, NULL, _FDEV_SETUP_WRITE);

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

static int printf_hook(char c, FILE* file) {
  if (c == '\n') print_char('\r');
  print_char(c);
  return 0;
}

//------------------------------------------------------------------------

int main() {
  print_init();
  printf("Testing: %d\n", 234);
  return 0;
}
