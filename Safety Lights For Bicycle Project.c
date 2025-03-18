#include <pic18f4520.h>
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 8000000
#include "project_1.h"

void main(void) {
while(1) {
// Motion Sensor Interrupt (INT0)
if (INTCONbits.INT0IF = 1) {
for(int i = 0; i < 9; i++){
PORTD = 0x01; // Turn on light at RD0
__delay_ms(100); // Wait for 3 seconds
PORTD = 0x00;
__delay_ms(100);// Turn off light
}
PORTD = 0x00;
__delay_ms(2000);
INTCONbits.INT0IF = 0; // Clear INT0 interrupt flag
}

// Headlight Interrupt (INT1) - Toggle Headlight Mode
if (INTCON3bits.INT1IF = 1) {
PORTD = 0x02; // Toggle light at RD1
__delay_ms(3000); // Wait for 3 seconds
PORTD = 0x00;
__delay_ms(2000);// Turn off light
INTCON3bits.INT1IF = 0; // Clear INT1 interrupt flag
}

// Brake Sensor Interrupt (INT2)
if (INTCON3bits.INT2IF = 1) {
PORTD = 0x04; // Turn on both lights (RD0 and RD1)
__delay_ms(3000); // Wait for 3 seconds
PORTD = 0x00;
__delay_ms(2000);// Turn off both lights
INTCON3bits.INT2IF = 0; // Clear INT2 interrupt flag
}

// Caution lights (RD4)
if (INTCONbits.INT0IF = 1) { // Trigger condition for caution lights (e.g., INT3 interrupt)
for (int i = 0; i < 6; i++) { // Flash RD4 for 3 seconds (6 times 100ms)
PORTD = 0x08; // Turn on RD4 (Right Turn Signal)
__delay_ms(500); // Wait for 100ms
PORTD = 0x00; // Turn off RD4
__delay_ms(500); // Wait for 100ms
}
PORTD = 0x00; // Ensure RD4 is off
__delay_ms(2000); // Wait for 3 seconds
INTCONbits.INT0IF = 0; // Clear INT3 interrupt flag
}


// Configure I/O
TRISB = 0xF7; // Configure RB0, RB1, RB2 as inputs
TRISD = 0x00; // Configure PORTD as output (for lights)

PORTB = 0xF7; // Set PORTB for motion sensor input
PORTD = 0x00; // Ensure PORTD is initially low

// Enable internal pull-ups for PORTB
INTCON2bits.RBPU = 0; // Disable the PORTB pull-ups

// Enable global interrupts
INTCONbits.GIE = 1; // Enable global interrupts
INTCONbits.PEIE = 1; // Enable peripheral interrupts

// Configure interrupts
INTCONbits.INT0IE = 1; // Enable INT0 (motion sensor)
INTCON3bits.INT1IE = 1; // Enable INT1 (headlight)
INTCON3bits.INT2IE = 1; // Enable INT2 (brake sensor)
INTCONbits.INT0IE = 1; // Enable INT3 (caution light)


// Configure falling edge interrupts for INT0, INT1, INT2
INTCON2bits.INTEDG0 = 0; // Falling edge for INT0 (motion sensor)
INTCON2bits.INTEDG1 = 0; // Falling edge for INT1 (headlight)
INTCON2bits.INTEDG2 = 0; // Falling edge for INT2 (brake sensor)
INTCON2bits.INTEDG0 = 0; // Falling edge for INT3 (caution light)


}
}