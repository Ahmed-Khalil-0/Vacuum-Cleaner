#include <stdio.h>
#include <stdlib.h>
#include "OS.h"
#include "sysControl.h"
#include "comparator.h"

void main(void)
{
    sysControl_Init();
    OS_Init();
    OS_Start();
    while(1){
    }
}
