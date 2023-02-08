#include <avr/io.h>
#include <serial.h>

#define MAX_BUFFER_SIZE 1024

//------------------------------------------------------------------------

static u8  uart_buffer[MAX_BUFFER_SIZE];
static int uart_buffer_size;

static u8  bus_buffer[MAX_BUFFER_SIZE];
static int bus_buffer_size;

//------------------------------------------------------------------------

void serial_init() {

}

//------------------------------------------------------------------------

void serial_task() {

}

//------------------------------------------------------------------------

// Bus interrupt
ISR (USART3_RXC_vect) {
  u8 data = USART3.RXDATAL;
}

//------------------------------------------------------------------------

// Jetson Nano UART interrupt
ISR (USART0_RXC_vect) {
  u8 data = USART0.RXDATAL;
  
}
