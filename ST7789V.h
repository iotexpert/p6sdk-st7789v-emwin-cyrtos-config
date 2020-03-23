#ifndef ST7789V_H
#define ST7789V_H
void ST7789V_Init(void);
void ST7789V_writeCommand(unsigned char command);
void ST7789V_writeData(unsigned char data);
void ST7789V_writeDataStream(unsigned char * pData, int numBytes);
unsigned char ST7789V_readData();
void ST7789V_readDataStream(unsigned char *data,int numItems);

#endif
