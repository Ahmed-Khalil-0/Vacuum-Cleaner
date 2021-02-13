#include "OS.h"
#include "sysControl.h"
#include "ssd.h"
#include "switch.h"
#include "comparator.h"
#include "motor.h"


static SW_State sw_state = released;
static speed_Level speed_level = mid;

void sysControl_Init(void){
    SSD_Buffer_Set(speed_level);
    SSD_Init();
    switch_Init(plus);
    switch_Init(minus);
    switch_Init(p_sw);
    comparator_Init();
    motor_Init();
}

void sysControl_Update(void){
    //every 20 ms read SWs STATE
    static tByte current_Loop = 0;
    current_Loop += 1;
    if(current_Loop < SYSCONTROL_LOOP){
        return;
    }
    current_Loop = 0;
        //process it -> out what happen

    //get plus switch state.
    //get current speed OR save current speed.
    switch_Get_State(plus, &sw_state);
        //if current speed != max -> incrment speed
        if(speed_level < max && sw_state == pressed){
            speed_level += 1;
            // write  display.
            SSD_Buffer_Set(speed_level);
            //pass additional info. to motor.
            sw_state = released;
        }

    //get minus switch state.
    //get current speed OR save current speed.
    switch_Get_State(minus, &sw_state);
        //if current speed != min -> decrement speed
        if(speed_level > min && sw_state == pressed){
            speed_level -= 1;
            // write  display.
            SSD_Buffer_Set(speed_level);
            //pass additional info. to motor.
            sw_state = released;
        }
}
