#include "gpio.h"

#define AS PF4
#define Ready PF3
#define VT PF1

// Subroutine reads AS input and waits for signal to be low
// If AS is already low, it returns right away
// If AS is currently high, it will wait until it to go low
// Inputs:  None
// Outputs: None
void WaitForASLow(void){
    while (AS != 0);
}

// Subroutine reads AS input and waits for signal to be high
// If AS is already high, it returns right away
// If AS is currently low, it will wait until it to go high
// Inputs:  None
// Outputs: None
void WaitForASHigh(void){
    while (AS == 0);
}

// Subroutine sets VT high
// Inputs:  None
// Outputs: None
// Notes:   friendly means it does not affect other bits in the port
void SetVT(void){
    VT |= 0x2;
}

// Subroutine clears VT low
// Inputs:  None
// Outputs: None
// Notes:   friendly means it does not affect other bits in the port
void ClearVT(void){
    VT &= ~0x2;
}

// Subroutine sets Ready high
// Inputs:  None
// Outputs: None
// Notes:   friendly means it does not affect other bits in the port
void SetReady(void){
    Ready |= 0x8;
}


// Subroutine clears Ready low
// Inputs:  None
// Outputs: None
// Notes:   friendly means it does not affect other bits in the port
void ClearReady(void){
    Ready &= ~0x8;
}

// Subroutine to delay in units of milliseconds
// Inputs:  Number of milliseconds to delay
// Outputs: None
// Notes:   assumes 80 MHz clock
void Delay1ms(unsigned long msec){
    // PF2 = 0x4;
    while (msec--) {
        unsigned long time = 1000;
        while (time) {
            time--;
        }
    }
    // PF2 = 0x0;
}

int main(void) {
    PortF_Init();

    while (1) {
        SetReady();
        WaitForASLow();
        ClearReady();
        Delay1ms(10);
        WaitForASHigh();
        Delay1ms(250);
        SetVT();
        Delay1ms(250);
        ClearVT();
    }
}

// Color    LED(s) PortF
// dark     ---    0
// red      R--    0x02
// blue     --B    0x04
// green    -G-    0x08
// yellow   RG-    0x0A
// sky blue -GB    0x0C
// white    RGB    0x0E
// pink     R-B    0x06
