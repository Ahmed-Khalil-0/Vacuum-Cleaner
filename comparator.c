#include "comparator.h"
#include "GPIO.h"
#include "OS.h"

void comparator_Init(void){
    GPIO_InitPortPin(GPIO_PORTA_CONTROL, GPIO_PIN_1, GPIO_IN);
    GPIO_InitPortPin(GPIO_PORTA_CONTROL, GPIO_PIN_2, GPIO_IN);
    GPIO_InitPortPin(GPIO_PORTD_CONTROL, GPIO_PIN_6, GPIO_OUT);
    GPIO_InitPortPin(GPIO_PORTD_CONTROL, GPIO_PIN_5, GPIO_OUT);
    // GPIO_InitPortPin(GPIO_PORTD_CONTROL, GPIO_PIN_7, GPIO_OUT);
    OUTPUT_NON_INVERTING;
    COMPARATOR_INTERRUPT_ENABLE;
    COMARATOR_MODE;
}

//as comparator each 0 volt its output -> high.

// tByte comparator_Read(void){
//     tByte ret = 0;
//     while(READ_COMPARATOR_OUTPUT != 1);
//     return ret;
// }
//
// void write_Pin(void){
//
// }

void comparator_Update(void){
    CLEAR_INTERRUPT;
    GPIO_WritePortPin(GPIO_PORTD_DATA, GPIO_PIN_6,CMIF);
    // while(CMIF != 1);
    // GPIO_WritePortPin(GPIO_PORTD_DATA, GPIO_PIN_7,READ_COMPARATOR_OUTPUT);
}
