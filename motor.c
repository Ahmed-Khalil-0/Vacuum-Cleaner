#include "motor.h"
#include "OS.h"
#include "GPIO.h"
#include "comparator.h"

static tByte current_Firing = mid_phase;
static tByte target_Firing = mid_phase;

void motor_Init(void){
    GPIO_InitPortPin(GPIO_PORTD_CONTROL, GPIO_PIN_3, GPIO_OUT);
}

// "pulse FIRING FUNC.".
    /*used to output Actual SIGNAL*/
void pulse_Firing(void){//--400us.
    //declear static var to count the NUMBER OF THE accessing
    static tByte current_Access = 0;
        //check if the number of accessing excced the 2.
        if(current_Access < PULSE_FIRING_LOOP){
            //turn on the output
            GPIO_WritePortPin(GPIO_PORTD_DATA, GPIO_PIN_3, PULSE_HIGH);
            current_Access += 1;

        }else{
            //turn off the output.
            GPIO_WritePortPin(GPIO_PORTD_DATA, GPIO_PIN_3, PULSE_LOW);
            //rest ACCESS COUNTER.
            current_Access = 0;
            //deActivate Zero Crossing detected.
            OS_Set_AP(DE_ACTIVE);
            CLEAR_INTERRUPT;
            READ_COMPARATOR_OUTPUT;
            return;
        }
}

void zero_Crossing_Update(void){//--10 ms.
    static tByte current_Loop = 0;
    current_Loop += 1;
    if(current_Loop < ZERO_CROSSING_LOOP){
        return;
    }
    current_Loop = 0;
    //set Zero_Crossing_Detected. ture
}

void firing_Update(void){//--dynamic ms.
    //check time for executing.
    static tByte current_Loop = 0;
    current_Loop += 1;
    //read global time
    if(current_Loop < current_Firing){
        return;
    }
    current_Loop = 0;
    //set Activepulse ture.
    //call "pulse FIRING FUNC.".
    OS_Set_AP(ACTIVE);
    // pulse_Firing();
}

void soft_Switching_Update(void){//--20ms.
    static tByte current_Loop = 0;
    current_Loop += 1;
    if(current_Loop < SOFT_SWITCHING_LOOP){
        return;
    }
    current_Loop = 0;
    if(current_Firing != target_Firing){
        if(current_Firing < target_Firing ){
            current_Firing += 1;
        }else{
            current_Firing -= 1;
        }
    }

}
