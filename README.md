# ST7789V - emWin - PSoC 6 SDK Configuration Files
This repository contains all of the emWin configuration files plus driver setup for the ST7789V (driver chip) connected the TFT display on the Cypress CY8CKIT-028-TFT.  These configiuration files will generically support displays with the ST7789V

This driver configures emWin to use FreeRTOS (e.g. for Delays)

To use this driver you need to
```
#include "ST7789V.h"
```

Before you startup emWin you need to configure the GPIOs and the screen by calling the initialization function.  The function prototype is:
```
void ST7789V_Init(cyhal_gpio_t RD,cyhal_gpio_t WR,cyhal_gpio_t DC,cyhal_gpio_t RST,
                cyhal_gpio_t DB8, cyhal_gpio_t DB9, cyhal_gpio_t DB10, cyhal_gpio_t DB11,
                cyhal_gpio_t DB12, cyhal_gpio_t DB13, cyhal_gpio_t DB14, cyhal_gpio_t DB15);
```

If you are using a Cypress development kit these configuration files contain an initialization function that calls the Init function for you with all of the pin aliases.  This function will only be available if there are BSP #defines for all of the required pins.  Here is the actual function.
```
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
```

These files depend on emWin being part of your project.  You must add them either manually or by using the library manager.  Do not forget that in order to use the emWin library you need to add the correct component to your makefile.
```
COMPONENTS=EMWIN_OSNTS
```


# Adding this Driver to your project manually
You can add this driver plus emWin to your project by:
```
echo "https://github.com/cypresssemiconductorco/emwin/#release-v5.48.1" > emwin.lib
echo "https://github.com/iotexpert/p6sdk-st7789v-emWin-config/#master" > p6sdk-ssd1306-emWin-config.lib
make getlibs
```
# Adding this Driver to your project with the Library Manager
If you are using the IoT Expert manifest this will show up in the library manager under the IoT Expert middleware.
![Exmaple Code Results](https://raw.githubusercontent.com/iotexpert/p6sdk-st7789v-emwin-cyrtos-config/master/libraryManager.png)

## Example Code
This code will initailize the BSP, then display "Hello World" in the middle.
```
#include "cybsp.h"
#include "cyhal.h"

#include "FreeRTOS.h"
#include "task.h"

#include "GUI.h"
#include "ST7789V.h"

void displayTask(void *arg)
{
	(void)arg;
//	ST7789V_InitBSP();
	ST7789V_Init(CYBSP_D10,CYBSP_D11,CYBSP_D12,CYBSP_D13,CYBSP_J2_2,CYBSP_J2_4,CYBSP_J2_6,CYBSP_J2_10,CYBSP_J2_12,CYBSP_D7,CYBSP_D8,CYBSP_D9);
	GUI_Init();
	GUI_SetColor(GUI_WHITE);
	GUI_SetBkColor(GUI_BLACK);
	GUI_SetFont(GUI_FONT_32B_ASCII);
	GUI_SetTextAlign(GUI_TA_CENTER);
	GUI_DispStringAt("Hello World", GUI_GetScreenSizeX()/2,GUI_GetScreenSizeY()/2 - GUI_GetFontSizeY()/2);
	vTaskSuspend( NULL );
}

int main(void)
{
    uxTopUsedPriority = configMAX_PRIORITIES - 1 ; // enable OpenOCD Thread Debugging

    cybsp_init() ;
    __enable_irq();

    setvbuf(stdin, NULL, _IONBF, 0);

    // Stack size in WORDs
    // Idle task = priority 0
    xTaskCreate(displayTask, "displayTask",2*configMINIMAL_STACK_SIZE,0 /* args */ ,1 /* priority */, 0);
    vTaskStartScheduler();
}

```

![Exmaple Code Results](https://raw.githubusercontent.com/iotexpert/p6sdk-st7789v-emwin-cyrtos-config/master/st7789v.jpg)
