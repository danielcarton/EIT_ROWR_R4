#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>
#include <util/delay.h>

static uint16_t pwm_to_cmp(unsigned char pwm) {
  uint32_t tmp = (uint32_t)(pwm - 1) * 6000;
  return 1500 + tmp / 254;
}

ISR (USART2_RXC_vect) {
  static volatile int index = 0;
  uint8_t data = USART2.RXDATAL;

  if (data == 0) {
    index = 0;
    return;
  }

  switch (index++) {
    case 0:  TCA0.SINGLE.CMP0 = pwm_to_cmp(data);  break;
    case 1:  TCA0.SINGLE.CMP1 = pwm_to_cmp(data);  break;
  }
}

int main() {
  ccp_write_io((uint8_t* )&CLKCTRL.MCLKCTRLB, 0);
  ccp_write_io((uint8_t* )&CLKCTRL.OSCHFCTRLA, CLKCTRL_FRQSEL_24M_gc);
  ccp_write_io((uint8_t* )&WDT.CTRLA, 0);

  PORTF.DIRSET = 1 << 0;
  PORTF.DIRCLR = 1 << 1;
  USART2.CTRLA = USART_RXCIE_bm;
  USART2.CTRLB = USART_TXEN_bm | USART_RXEN_bm;
  USART2.BAUD  = 4 * F_CPU / 230400;

  PORTA.DIRSET      = 0b111;
  TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_SINGLESLOPE_gc | TCA_SINGLE_CMP0EN_bm | TCA_SINGLE_CMP1EN_bm;
  TCA0.SINGLE.CMP0  = pwm_to_cmp(128);
  TCA0.SINGLE.CMP1  = pwm_to_cmp(128);
  TCA0.SINGLE.PER   = 60000;
  TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV8_gc | TCA_SINGLE_ENABLE_bm;

  sei();
  while (1);
  return 0;
}
