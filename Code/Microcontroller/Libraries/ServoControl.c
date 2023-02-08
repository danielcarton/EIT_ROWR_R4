#include <AVRlib.h>
#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#include "I2CControl.h"
#include "ServoControl.h"

#define SERVO_SIG_FREQ 50 // 50 Hz
#define CLK_FREQ 24000000 // 24 MHz

void init_servo(void)
{
    // set TCA to 50Hz
    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc; // 16MHz
    TCA0.SINGLE.PER = CLK_FREQ / (SERVO_SIG_FREQ * 256) - 1; // 50Hz
}