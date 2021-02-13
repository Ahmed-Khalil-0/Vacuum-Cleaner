#include "OS.h"
#include "GPIO.h"
#include "ssd.h"

//set of symbols for drawing speed levels.
static tByte ssd_Symbols[SSD_SYMBOL_SIZE] = {
    0b11110111,
    0b10110111,
    0b10110110,
    0b11111111
};

tByte ssd_Buffer[DISPLAY_BUFFER_SIZE] = {null,null,null};

//init buffer -> port B ccontrol and data -> port D "SSD CONTROL".
void SSD_Init(void){
    GPIO_InitPort(GPIO_PORTB_CONTROL, GPIO_OUT);
    GPIO_WritePort(GPIO_PORTB_DATA, ssd_Symbols[null]);
    GPIO_InitPortPin(GPIO_PORTD_CONTROL, GPIO_PIN_0, GPIO_OUT);
    GPIO_InitPortPin(GPIO_PORTD_CONTROL, GPIO_PIN_1, GPIO_OUT);
    GPIO_InitPortPin(GPIO_PORTD_CONTROL, GPIO_PIN_2, GPIO_OUT);
}

//buffer "function write into"  & "function read from".
void SSD_Update(void){
    //check if ur time came.
    static tByte current_Loop = 0;
    static speed_Level speed = min;
    current_Loop += 1;
    if(current_Loop < SSD_LOOP){
        return;
    }
    current_Loop = 0;

    //turn off all SSD.
    GPIO_WritePortPin(GPIO_PORTD_DATA, GPIO_PIN_0, SSD_OFF);
    GPIO_WritePortPin(GPIO_PORTD_DATA, GPIO_PIN_1, SSD_OFF);
    GPIO_WritePortPin(GPIO_PORTD_DATA, GPIO_PIN_2, SSD_OFF);

    //display data.
    GPIO_WritePort(GPIO_PORTB_DATA, ssd_Symbols[ssd_Buffer[speed]]);

    //which SSD ON.
    GPIO_WritePortPin(GPIO_PORTD_DATA, speed, SSD_ON);

    speed += 1;
    //if reach end look at buffer 0
    if(speed > max){
        speed = min;
    }
}//5ms.

//outer module to set buffer values.
void SSD_Buffer_Set(speed_Level speed_level){
    switch(speed_level){
        case max:
            ssd_Buffer[max] = max;
        break;
        case mid:
            ssd_Buffer[max] = null;
            ssd_Buffer[mid] = mid;
            ssd_Buffer[min] = min;
        break;
        case min:
            ssd_Buffer[max] = null;
            ssd_Buffer[mid] = null;
            ssd_Buffer[min] = min;
        break;
        default:
        break;
    }
}
