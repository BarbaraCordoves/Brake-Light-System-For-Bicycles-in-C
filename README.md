PIC18F4520 Automotive Lighting System:
A micro-controller-based system written in C for the PIC18F4520 that manages various automotive lighting functions based on external interrupt triggers.

Features:
This project implements event-driven control for several lighting components using external interrupts:

  - Motion Sensor Light (INT0): Triggers a sequence of 9 flashes on RD0 (light) when motion is detected.
  - Headlight Toggle (INT1): Toggles a light on RD1 for a duration when activated.
  - Brake Sensor Light (INT2): Activates a "brake light" on RD2 for a duration upon sensing a brake event.
  - Caution/Turn Signal Light (INT3): Flashes a light on RD3 repeatedly as a caution or turn signal indicator.

Hardware and Software Requirements:
Hardware:
   - Microcontroller: PIC18F4520
   - Programmer/Debugger: PICKit 3/4 or equivalent.
   - Input Devices: Switches or sensors connected to RB0 (INT0), RB1 (INT1), RB2(INT2), and TB3 (INT3).
   - Output Devices: LEDs (with appropriate current-limiting resistors) or relay drivers connected to PORTD pins (RDO-RD3).

Software:
   - IDE: MPLAB X IDECompiler: XC8 Compiler (tested with $\text{v1.34}$ or newer)
   - Header Files: Standard pic18f4520.h, xc.h, stdio.h, and a project-specific project_1.h

Configuration and Setup:
Clock Frequency:
The system is configured to run at an internal clock frequency of 8 MHz.
   - #define_XTAL_FREQ 8000000

I/O Pin Configuration
   - Inputs: RB0, RB1, RB2, RB3 are configured as inputs for the external interrupt pins.
   - Note: The code attempts to configure TRISB = 0xF7 (which sets RB3 to output and RB0, RB1, RB2 to input), but the intent is likely to set RB0-RB3 as inputs (TRISB = 0xF0). The provided code will work for INT0, INT1, INT2 but may require adjustment if INT3 is intended to be used on RB3.
   - Outputs: PORTD is configured entirely as output (TRISD = 0x00}$) to control the lights.
   - Interrupts: All external interrupts (INT0, INT1, INT2, INT3) are configured for a falling edge trigger.

Interrupt Configuration Registers:
The following registers are configured in the code:
   - INTCONbits.GIE = 1: Global Interrupt Enable.
   - INTCONbits.PEIE = 1: Peripheral Interrupt Enable.
   - INTCONbits.INT0IE = 1: Enable INT0.
   - INTCON3bits.INT1IE = 1: Enable INT1.
   - INTCON3bits.INT2IE = 1: Enable INT2.
   - INTCON2bits.INTEDG0 = 0: Falling edge for INT0.
   - INTCON2bits.INTEDG1 = 0: Falling edge for INT1.

INTCON2bits.INTEDG2 = 0: Falling edge for INT2.

Code Implementation Details:
The main control logic is implemented within the main() function's super-loop (while(1)).
    Critical Note on Interrupt Handling: The current code polls the interrupt flags (INT0IF, INT1IF, INT2IF, INT3IF) inside the while(1) loop instead of using a dedicated Interrupt Service Routine (ISR).
   - Polling Approach (Current): The lights' functions are executed in the main loop, which stops the controller from doing anything else during the delay calls.
        - Example: if (INTCONbits.INT0IF = 1) (Note: This is an assignment (=) and not a comparison (==); it should be fixed for correct polling logic.)
   - ISR Approach (Recommended): For true, non-blocking interrupt handling, the light logic should be moved to a separate function:

//
void __interrupt() MyInterruptHandler(void) {
    if (INTCONbits.INT0IF == 1) {
        // Handle motion sensor logic (ideally set a flag)
        INTCONbits.INT0IF = 0;
    }
    // ... other interrupt handlers
}
//

The main loop would then only check and process the flags set by the ISR, allowing for more responsive system behavior.

Usage:
Clone the repository:
   1. git clone [repository-link]
     cd pic18f4520-auto-lights
   2. Open in MPLAB X IDE: Load the project files (main.c and header files).
   3. Compile: Build the project using the XC8 compiler to generate the .hex file.
   4. Flash the Microcontroller: Use your PICKit programmer to load the generated .hex file onto the PIC18F4520.
   5. Connect Inputs/Outputs: Connect the input switches/sensors to RB0-RB3 and the output lights to RD0-RD3.
   6. Test: Trigger the inputs (e.g., press a button on RB0}) and observe the corresponding light behavior on PORTD.


