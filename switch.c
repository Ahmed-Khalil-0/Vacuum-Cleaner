#include "OS.h"
#include "switch.h"
#include "GPIO.h"
typedef struct{
    tByte sample_Value[NUM_OF_SAMPLES];
    // SW_state sample_State[NUM_OF_SAMPLES];
    SW_State SW_state[NUM_OF_SAMPLES];
    SW_State SW_final_state;
    // tByte Time_Out;
}SW_Info;

static SW_Info SWs_Data[NUM_OF_SWITCHS];

void switch_Init(SW_Name sw_name){
    switch(sw_name){
        case plus:
            GPIO_InitPortPin(GPIO_PORTC_CONTROL, GPIO_PIN_0, GPIO_IN);
            break;
        case minus:
            GPIO_InitPortPin(GPIO_PORTC_CONTROL, GPIO_PIN_1, GPIO_IN);
            break;
        case p_sw:
            GPIO_InitPortPin(GPIO_PORTC_CONTROL, GPIO_PIN_2, GPIO_IN);
            break;
        default:
            break;
    }
    SWs_Data[sw_name].sample_Value[0] = released;
    SWs_Data[sw_name].sample_Value[1] = released;
    SWs_Data[sw_name].SW_state[0] = released;
    SWs_Data[sw_name].SW_state[1] = released;
    SWs_Data[sw_name].SW_final_state = released;
}

void switch_Update(void){
    //move throw switch's DATA
    SW_Name sw_name = plus;
    static tByte current_Loop = 0;
    current_Loop += 1;
    if(current_Loop < SW_LOOP){
        return;
    }
    current_Loop = 0;
    while(sw_name <= p_sw){
        //take new sample.
        //place the status in the current.
        SWs_Data[sw_name].sample_Value[1] = GPIO_ReadPortPin(GPIO_PORTC_DATA, sw_name);
        //calculate the status of switch. -> switch
        if((SWs_Data[sw_name].sample_Value[0] == 0)  && (SWs_Data[sw_name].sample_Value[1] == 0)){
            SWs_Data[sw_name].SW_state[1] = pressed;
                //if equal in PRESSED
        }
        else{
            //else final state = RELEASED
            SWs_Data[sw_name].SW_state[1] = released;
        }

        //compare with previous status.
        //if previous sampleState(PRESSED) && current sampleState(RELEASED)
        //set final state = pressed.
        if((SWs_Data[sw_name].SW_state[0] == pressed) && (SWs_Data[sw_name].SW_state[1] == released)){
            SWs_Data[sw_name].SW_final_state = pressed;
        }
        else{
            SWs_Data[sw_name].SW_final_state = released;
        }
        //move current sampleValue to previous.
         SWs_Data[sw_name].sample_Value[0] = SWs_Data[sw_name].sample_Value[1];
         //move current stateValue to previous.
         SWs_Data[sw_name].SW_state[0] = SWs_Data[sw_name].SW_state[1];
         sw_name += 1;
    }
}

void switch_Get_State(SW_Name sw_name,SW_State* sw_state){
    *sw_state = SWs_Data[sw_name].SW_final_state;
}
