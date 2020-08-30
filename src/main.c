#include "gpio.h"

void delay(void) {
    unsigned long volatile time;
    time = 100000;
    while (time) {
        time--;
    }
}

int main(void) {
    PortF_Init();
    PF2 = 4;
    // GPIO_PORTF_DATA_R = 0x08;
    while (1) {
        delay();
        if(PF4 == 0x0){
            PF2 = 0;
            delay();
            PF2 = 4;
        } else {
            PF2 = 4;
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
