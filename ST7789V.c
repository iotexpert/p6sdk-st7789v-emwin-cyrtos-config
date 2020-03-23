#include "cyhal.h"
#include "cybsp.h"
#include "GUI.h"

void ST7789V_InitConfig();

static cyhal_gpio_t TFT_RD;
static cyhal_gpio_t TFT_WR;
static cyhal_gpio_t TFT_DC;
static cyhal_gpio_t TFT_RST;

static cyhal_gpio_t TFT_DB8;
static cyhal_gpio_t TFT_DB9;
static cyhal_gpio_t TFT_DB10;
static cyhal_gpio_t TFT_DB11;
static cyhal_gpio_t TFT_DB12;
static cyhal_gpio_t TFT_DB13;
static cyhal_gpio_t TFT_DB14;
static cyhal_gpio_t TFT_DB15;

// This function configures attaches this driver to the actual hardware pins on the ST7789V

void ST7789V_Init(cyhal_gpio_t RD,cyhal_gpio_t WR,cyhal_gpio_t DC,cyhal_gpio_t RST,
                cyhal_gpio_t DB8, cyhal_gpio_t DB9, cyhal_gpio_t DB10, cyhal_gpio_t DB11,
                cyhal_gpio_t DB12, cyhal_gpio_t DB13, cyhal_gpio_t DB14, cyhal_gpio_t DB15
                )
{
    TFT_RD  = RD;
    TFT_WR  = WR;
    TFT_DC  = DC;
    TFT_RST = RST;
    TFT_DB8  = DB8;
    TFT_DB9  = DB9;
    TFT_DB10 = DB10;
    TFT_DB11 = DB11;
    TFT_DB12 = DB12;
    TFT_DB13 = DB13;
    TFT_DB14 = DB14;
    TFT_DB15 = DB15;

    cyhal_gpio_init(TFT_RD ,CYHAL_GPIO_DIR_OUTPUT,CYHAL_GPIO_DRIVE_STRONG,0);
    cyhal_gpio_init(TFT_WR ,CYHAL_GPIO_DIR_OUTPUT,CYHAL_GPIO_DRIVE_STRONG,0);
    cyhal_gpio_init(TFT_DC ,CYHAL_GPIO_DIR_OUTPUT,CYHAL_GPIO_DRIVE_STRONG,0);
    cyhal_gpio_init(TFT_RST,CYHAL_GPIO_DIR_OUTPUT,CYHAL_GPIO_DRIVE_STRONG,0);
    
    cyhal_gpio_init(TFT_DB8,CYHAL_GPIO_DIR_OUTPUT,CYHAL_GPIO_DRIVE_STRONG,0);
    cyhal_gpio_init(TFT_DB9,CYHAL_GPIO_DIR_OUTPUT,CYHAL_GPIO_DRIVE_STRONG,0);
    cyhal_gpio_init(TFT_DB10,CYHAL_GPIO_DIR_OUTPUT,CYHAL_GPIO_DRIVE_STRONG,0);
    cyhal_gpio_init(TFT_DB11,CYHAL_GPIO_DIR_OUTPUT,CYHAL_GPIO_DRIVE_STRONG,0);
    cyhal_gpio_init(TFT_DB12,CYHAL_GPIO_DIR_OUTPUT,CYHAL_GPIO_DRIVE_STRONG,0);
    cyhal_gpio_init(TFT_DB13,CYHAL_GPIO_DIR_OUTPUT,CYHAL_GPIO_DRIVE_STRONG,0);
    cyhal_gpio_init(TFT_DB14,CYHAL_GPIO_DIR_OUTPUT,CYHAL_GPIO_DRIVE_STRONG,0);
    cyhal_gpio_init(TFT_DB15,CYHAL_GPIO_DIR_OUTPUT,CYHAL_GPIO_DRIVE_STRONG,0);

    ST7789V_InitConfig();

}

// If the BSP pins are defined that are connected to the CY8CKIT-028-TFT sheild then provide the function
// that initializes those pins.

#if defined(CYBSP_D10) &defined(CYBSP_D11) & defined(CYBSP_D12) & defined(CYBSP_D13) & defined(CYBSP_J2_2) & \
    defined(CYBSP_J2_4) & defined(CYBSP_J2_6) & defined(CYBSP_J2_10) & defined(CYBSP_J2_12) & defined(CYBSP_D7) & \
    defined(CYBSP_D8) & defined(CYBSP_D9)
void ST7789V_InitBSP()
{
    ST7789V_Init(CYBSP_D10,CYBSP_D11,CYBSP_D12,CYBSP_D13,CYBSP_J2_2,CYBSP_J2_4,CYBSP_J2_6,CYBSP_J2_10,CYBSP_J2_12,CYBSP_D7,CYBSP_D8,CYBSP_D9);
}
#endif

// Bit Bang the ST7789V bus
void ST7789V_CTRL_Write(unsigned char data)
{
    cyhal_gpio_write(TFT_DB8  ,(data>>0) & 0x01);
    cyhal_gpio_write(TFT_DB9  ,(data>>1) & 0x01);
    cyhal_gpio_write(TFT_DB10 ,(data>>2) & 0x01);
    cyhal_gpio_write(TFT_DB11 ,(data>>3) & 0x01);
    cyhal_gpio_write(TFT_DB12 ,(data>>4) & 0x01);
    cyhal_gpio_write(TFT_DB13 ,(data>>5) & 0x01);
    cyhal_gpio_write(TFT_DB14 ,(data>>6) & 0x01);
    cyhal_gpio_write(TFT_DB15 ,(data>>7) & 0x01);
}

void ST7789V_writeCommand(unsigned char command)
{
    cyhal_gpio_write(TFT_DC,0);
    ST7789V_CTRL_Write(command);
    cyhal_gpio_write(TFT_WR,0);
    cyhal_gpio_write(TFT_WR,1);
}

void ST7789V_writeData(unsigned char data)
{
    cyhal_gpio_write(TFT_DC,1);
    ST7789V_CTRL_Write(data);
    cyhal_gpio_write(TFT_WR,0);
    cyhal_gpio_write(TFT_WR,1);
}

void ST7789V_InitConfig(void)
{
    cyhal_gpio_write(TFT_DC,0);
        cyhal_gpio_write(TFT_RD,1);
        cyhal_gpio_write(TFT_WR,0);
        cyhal_gpio_write(TFT_RST,0);

    GUI_X_Delay(100);
    cyhal_gpio_write(TFT_RST,1);

    GUI_X_Delay(100);

    ST7789V_writeCommand(0x11);    /* exit SLEEP mode*/

    GUI_X_Delay(300);

    ST7789V_writeCommand(0x36);
    ST7789V_writeData(0xA0);      /* MADCTL: memory data access control*/
    ST7789V_writeCommand(0x3A);
    ST7789V_writeData(0x65);      /* COLMOD: Interface Pixel format*/
    ST7789V_writeCommand(0xB2);
    ST7789V_writeData(0x0C);
    ST7789V_writeData(0x0C);
    ST7789V_writeData(0x00);
    ST7789V_writeData(0x33);
    ST7789V_writeData(0x33); /*PORCTRK: Porch setting*/
    ST7789V_writeCommand(0xB7);
    ST7789V_writeData(0x35); /*GCTRL: Gate Control*/
    ST7789V_writeCommand(0xBB);
    ST7789V_writeData(0x2B); /*VCOMS: VCOM setting*/
    ST7789V_writeCommand(0xC0);
    ST7789V_writeData(0x2C); /*LCMCTRL: LCM Control*/
    ST7789V_writeCommand(0xC2);
    ST7789V_writeData(0x01);
    ST7789V_writeData(0xFF); /*VDVVRHEN: VDV and VRH Command Enable*/
    ST7789V_writeCommand(0xC3);
    ST7789V_writeData(0x11); /*VRHS: VRH Set*/
    ST7789V_writeCommand(0xC4);
    ST7789V_writeData(0x20); /*VDVS: VDV Set*/

    ST7789V_writeCommand(0xC6);
    ST7789V_writeData(0x0F); /*FRCTRL2: Frame Rate control in normal mode*/
    ST7789V_writeCommand(0xD0);
    ST7789V_writeData(0xA4);
    ST7789V_writeData(0xA1); /*PWCTRL1: Power Control 1*/
    ST7789V_writeCommand(0xE0);
    ST7789V_writeData(0xD0);
    ST7789V_writeData(0x00);
    ST7789V_writeData(0x05);
    ST7789V_writeData(0x0E);
    ST7789V_writeData(0x15);
    ST7789V_writeData(0x0D);
    ST7789V_writeData(0x37);
    ST7789V_writeData(0x43);
    ST7789V_writeData(0x47);
    ST7789V_writeData(0x09);
    ST7789V_writeData(0x15);
    ST7789V_writeData(0x12);
    ST7789V_writeData(0x16);
    ST7789V_writeData(0x19); /*PVGAMCTRL: Positive Voltage Gamma control*/
    ST7789V_writeCommand(0xE1);
    ST7789V_writeData(0xD0);
    ST7789V_writeData(0x00);
    ST7789V_writeData(0x05);
    ST7789V_writeData(0x0D);
    ST7789V_writeData(0x0C);
    ST7789V_writeData(0x06);
    ST7789V_writeData(0x2D);
    ST7789V_writeData(0x44);
    ST7789V_writeData(0x40);
    ST7789V_writeData(0x0E);
    ST7789V_writeData(0x1C);
    ST7789V_writeData(0x18);
    ST7789V_writeData(0x16);
    ST7789V_writeData(0x19); /*NVGAMCTRL: Negative Voltage Gamma control*/
    ST7789V_writeCommand(0x2A);
    ST7789V_writeData(0x00);
    ST7789V_writeData(0x00);
    ST7789V_writeData(0x01);
    ST7789V_writeData(0x3F); /*X address set*/
    ST7789V_writeCommand(0x2B);
    ST7789V_writeData(0x00);
    ST7789V_writeData(0x00);
    ST7789V_writeData(0x00);
    ST7789V_writeData(0xEF); /*Y address set*/

    GUI_X_Delay(10);
    ST7789V_writeCommand(0x29); /*Enable Display*/

}

void ST7789V_writeDataStream(unsigned char * pData, int numBytes)
{
    for(int i=0;i<numBytes;i++)
    {
        ST7789V_writeData(pData[i]);
    }
}

unsigned char ST7789V_readData()
{
    CY_ASSERT(0); // This function should never be called by emWin
    return 0; // never reaches here
}
void ST7789V_readDataStream(unsigned char *data,int numItems)
{
    CY_ASSERT(0); // This function should never be called by emWin
}
