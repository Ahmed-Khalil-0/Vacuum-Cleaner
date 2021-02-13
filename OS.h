#ifndef __OS_H__
#define __OS_H__

#define OS_TICK (200)

typedef unsigned char tByte;
typedef unsigned int tWord;

void OS_Init(void);
void OS_Start(void);
void OS_Update(void) __interrupt 0;
void OS_Set_AP(tByte);

#endif //__OS_H__
