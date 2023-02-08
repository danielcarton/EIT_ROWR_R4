#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>
#include <stdio.h>
#include <serial.h>
#include <print.h>
#include <basic.h>

//------------------------------------------------------------------------

static void system_init() {
  // Set CPU frequency to 24 MHz
  ccp_write_io((u8* )&CLKCTRL.MCLKCTRLB, 0);
  ccp_write_io((u8* )&CLKCTRL.OSCHFCTRLA, CLKCTRL_FRQSEL_24M_gc);
  ccp_write_io((u8* )&WDT.CTRLA, 0);

  // Enable global interrupts
  sei();
}

//------------------------------------------------------------------------

void main() {
  system_init();
  print_init();
  serial_task();

  while (1) {
    serial_task();
  }
}
