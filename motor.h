#ifndef __MOTOR_H__
#define __MOTOR_H__

typedef enum{
    low_phase = 0,
    mid_phase = 23,
    high_phase = 47
}firing_Position;

#define DETECTED (1)
#define NOT_DETECTED (0)

#define ACTIVE (1)
#define DE_ACTIVE (0)

#define PULSE_HIGH (1)
#define PULSE_LOW  (0)


#define PULSE_FIRING_LOOP   (2)
#define ZERO_CROSSING_LOOP  (50)
#define SOFT_SWITCHING_LOOP (100)

void motor_Init(void);

void zero_Crossing_Update(void);//10 ms.
//managed by Zero Crossing function.
void firing_Update(void);//dynamic time allocated
void pulse_Firing(void);

void soft_Switching_Update(void);//every 20 ms.

#endif //__MOTOR_H__
