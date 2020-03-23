#ifndef ST7789V_H
#define ST7789V_H

#include "cyhal.h"

void ST7789V_Init(cyhal_gpio_t RD,cyhal_gpio_t WR,cyhal_gpio_t DC,cyhal_gpio_t RST,
                cyhal_gpio_t DB8, cyhal_gpio_t DB9, cyhal_gpio_t DB10, cyhal_gpio_t DB11,
                cyhal_gpio_t DB12, cyhal_gpio_t DB13, cyhal_gpio_t DB14, cyhal_gpio_t DB15);
void ST7789V_InitBSP(void);

void ST7789V_writeCommand(unsigned char command);
void ST7789V_writeData(unsigned char data);
void ST7789V_writeDataStream(unsigned char * pData, int numBytes);
unsigned char ST7789V_readData();
void ST7789V_readDataStream(unsigned char *data,int numItems);

#endif
