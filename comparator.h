#ifndef __COMPARATOR_H__
#define __COMPARATOR_H__
#include <pic16f877a.h>

#define COMARATOR_MODE CM0 = 1;\
                       CM1 = 1;\
                       CM2 = 0

#define READ_COMPARATOR_OUTPUT (C2OUT)
#define COMPARATOR_INTERRUPT_ENABLE CMIE = 1;\
                                    PEIE = 1
#define CLEAR_INTERRUPT (CMIF = 0)

#define OUTPUT_NON_INVERTING (C2INV = 0)

void comparator_Init(void);
// tByte comparator_Read(void);
// void write_Pin(void);
void comparator_Update(void);

#endif //__COMPARATOR_H__
