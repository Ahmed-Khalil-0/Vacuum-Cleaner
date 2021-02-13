#include "OS.h"
#include "timer.h"
#include "ssd.h"
#include "switch.h"
#include "sysControl.h"
#include "comparator.h"
#include "motor.h"

static tByte active_pulse = DE_ACTIVE;

void OS_Init(void){
    TIMER_PRESCAlER;
    UPDATE_TIMER;
    PRESCALER_RATE_SELECT;
}

void OS_Start(void){
    CLEAR_TIMER_FLAG;
    ENABLE_INTERRUPT;
    ENABLE_GLOBAL_INTERRUPT;
    UPDATE_TIMER;
    ENABLE_TIMER;
}


//execute when interrupt came from timer...
void OS_Update(void) __interrupt 0{
    CLEAR_TIMER_FLAG;
    UPDATE_TIMER;
    // SSD_Update();
    // switch_Update();
    // sysControl_Update();
    // comparator_Update();
    // zero_Crossing_Update();
    if(CMIF == DETECTED){
        firing_Update();
        if(active_pulse == ACTIVE){
            pulse_Firing();
        }
    }
    //soft_Switching_Update();
}

void OS_Set_AP(tByte ap){
    active_pulse = ap;
}
