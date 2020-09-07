#include "gpio.h"
#include "tm4c123gh6pm.h"

void SysTick_Init(void){
    NVIC_ST_CTRL_R = 0;              // 1) disable SysTick during setup
    NVIC_ST_RELOAD_R = 4000000;      // 2) maximum reload value
    NVIC_ST_CURRENT_R = 0;           // 3) any write to current clears it
    NVIC_ST_CTRL_R = 0x00000005;     // 4) enable SysTick with core clock
}

unsigned long data[50];
int data_size = 0;

int main(void) {
    PortF_Init();
    SysTick_Init();

    unsigned long last = PF0 | PF4;

    while (1) {
        unsigned long current = PF0 | PF4;

        // PF2 = !!(current & 0x1)  << 2;
        // PF3 = !!(current & 0x10) << 3;

        if (data_size < 50 && last != current) {
            last = current;
            data[data_size++] = (current & 0x11) | PF1;
        }

        if (PF0 == 0 || PF4 == 0) {
            if (NVIC_ST_CTRL_R & 0x10000) {
                PF1 ^= 0x2;
            }
        } else {
            PF1 = 0;
            NVIC_ST_CURRENT_R = 0;
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
