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

#define PE0   (*((volatile unsigned long *)0x40024004))
void Switch_Init(void){ volatile unsigned long delay;
    SYSCTL_RCGC2_R |= 0x00000010;
    delay = SYSCTL_RCGC2_R;

    GPIO_PORTE_AMSEL_R &= ~0x01;
    GPIO_PORTE_PCTL_R &= ~0x0000000F;
    GPIO_PORTE_DIR_R &= ~0x01;
    GPIO_PORTE_AFSEL_R &= ~0x01;
    GPIO_PORTE_DEN_R |= 0x01;
}

unsigned long Switch_Input(void){
    return PE0;
}

#define PE1   (*((volatile unsigned long *)0x40024008))
void LED_Init(void){
    volatile unsigned long delay;
    SYSCTL_RCGC2_R |= 0x10;
    delay = SYSCTL_RCGC2_R;

    GPIO_PORTE_PCTL_R &= ~0x000000F0;
    GPIO_PORTE_AMSEL_R &= ~0x02;
    GPIO_PORTE_DIR_R |= 0x02;
    GPIO_PORTE_AFSEL_R &= ~0x02;
    GPIO_PORTE_DEN_R |= 0x02;
}

void LED_On(void){
    PE1 |= 0x02;
}

void LED_Off(void){
    PE1 &= ~0x02;
}

int main(void) {
    PortF_Init();
    Switch_Init();
    LED_Init();

    while (1) {
        LED_On();
        Delay1ms(100);
        if (Switch_Input()) {
            LED_Off();
        }
        Delay1ms(100);
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
