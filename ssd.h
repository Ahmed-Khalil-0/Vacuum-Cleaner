#ifndef __SSD_H__
#define __SSD_H__

typedef enum{
    min = 0,
    mid,
    max,
    null
} speed_Level;

#define SSD_ON  (1)
#define SSD_OFF (0)

#define SSD_LOOP (25)
#define SSD_SYMBOL_SIZE (4)
#define DISPLAY_BUFFER_SIZE (3)

void SSD_Init(void);
void SSD_Update(void);//5ms.
void SSD_Buffer_Set(speed_Level);

#endif //__SSD_H__
