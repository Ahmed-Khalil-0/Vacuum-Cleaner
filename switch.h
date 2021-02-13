#ifndef __SWITCH_H__
#define __SWITCH_H__

#define NUM_OF_SAMPLES 2
#define NUM_OF_SWITCHS 3

#define SW_LOOP (100)

typedef enum{
    pressed = 0,
    released
}SW_State;

//switch names.
typedef enum{
    plus = 0,
    minus,
    p_sw
}SW_Name;

void switch_Init(SW_Name sw_name);
void switch_Update(void);
void switch_Get_State(SW_Name,SW_State*);
#endif //__SWITCH_H__
