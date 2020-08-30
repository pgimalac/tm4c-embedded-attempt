#include "gpio.h"

void Delay(void) {
    unsigned long volatile time;
    time = 800000;
    while (time) {
        time--;
    }
}

int main(void) {
    PortF_Init();
    while (1) {
        if(PF4 == 0x0){
            if (PF0 == 0x0) {
                GPIO_PORTF_DATA_R = 0x04;
            } else {
                GPIO_PORTF_DATA_R = 0x02;
            }
        } else {
            if (PF0 == 0x0) {
                GPIO_PORTF_DATA_R = 0x08;
            } else {
                GPIO_PORTF_DATA_R = 0x00;
            }
        }
        // Delay();
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
