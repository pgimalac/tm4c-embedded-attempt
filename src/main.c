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

#define PA5   (*((volatile unsigned long *)0x40004080))
void Switch_Init(void){
    volatile unsigned long delay;
    SYSCTL_RCGC2_R |= 0x00000001;     // 1) activate clock for Port A
    delay = SYSCTL_RCGC2_R;           // allow time for clock to start
                                      // 2) no need to unlock GPIO Port A
    GPIO_PORTA_AMSEL_R &= ~0x20;      // 3) disable analog on PA5
    GPIO_PORTA_PCTL_R &= ~0x00F00000; // 4) PCTL GPIO on PA5
    GPIO_PORTA_DIR_R &= ~0x20;        // 5) direction PA5 input
    GPIO_PORTA_AFSEL_R &= ~0x20;      // 6) PA5 regular port function
    GPIO_PORTA_DEN_R |= 0x20;         // 7) enable PA5 digital port
}

unsigned long Switch_Input(void){
  return PA5; // return 0x20(pressed) or 0(not pressed)
}

unsigned long Switch_Input2(void){
  return (GPIO_PORTA_DATA_R&0x20); // 0x20(pressed) or 0(not pressed)
}

int main(void) {
    PortF_Init();
    Switch_Init();

    while (1) {
        if (Switch_Input()) {
            PF2 = 0x4;
        } else {
            PF2 = 0x0;
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
