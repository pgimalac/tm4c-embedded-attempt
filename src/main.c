#include "gpio.h"
#include "tm4c123gh6pm.h"

void Delay1ms(unsigned long msec){
    while (msec--) {
        unsigned long time = 1000;
        while (time) {
            time--;
        }
    }
}

void LED_Init(void){
    volatile unsigned long delay;
    SYSCTL_RCGC2_R |= 0x01;           // 1) activate clock for Port A
    delay = SYSCTL_RCGC2_R;           // allow time for clock to start
                                    // 2) no need to unlock PA2
    GPIO_PORTA_PCTL_R &= ~0x00000F00; // 3) regular GPIO
    GPIO_PORTA_AMSEL_R &= ~0x04;      // 4) disable analog function on PA2
    GPIO_PORTA_DIR_R |= 0x04;         // 5) set direction to output
    GPIO_PORTA_AFSEL_R &= ~0x04;      // 6) regular port function
    GPIO_PORTA_DEN_R |= 0x04;         // 7) enable digital port
}

// Make PA2 high
void LED_On(void){
    GPIO_PORTA_DATA_R |= 0x04;
}

// Make PA2 low
void LED_Off(void){
    GPIO_PORTA_DATA_R &= ~0x04;
}

int main(void) {
    PortF_Init();
    LED_Init();

    while (1) {
        if (PF4 == 0) {
            LED_On();
        } else {
            LED_Off();
        }
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
