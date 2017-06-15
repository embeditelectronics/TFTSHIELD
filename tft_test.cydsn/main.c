/*******************************************************************************
* \file main.c
* \brief This file is used to demonstrate the TFTSHIELD API.
*
* Version 1.0
*
* \author Robert Barron
*
* \bug 
*******************************************************************************/
#include <project.h>
#include "stdio.h"

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000
long mapCoor(long x, long in_min, long in_max, long out_min, long out_max);

int main()
{   
    //initializes tft
    CyDelay(1000);
    Clock_1_SetDividerValue(24);
    CyDelay(10);
    //TFTSHIELD_1_StartTouch();
    bool touch_en = 0;
    uint16_t x, y;
    uint8_t z, buf;
    char buffer[50];
    
    while(!TFTSHIELD_1_StartTouch())
    {
       
    }
    touch_en = 1;
    Clock_1_SetDividerValue(1);
    CyDelay(10);
    TFTSHIELD_1_Start();
    
    TFTSHIELD_1_FillScreen(BLACK);
    //start at 0,0 for text
    TFTSHIELD_1_SetCursor(0,0);
    TFTSHIELD_1_SetTextColor(WHITE);  
    TFTSHIELD_1_SetTextSize(2);
    
    //landscape orientation
    TFTSHIELD_1_SetRotation(0);
    TFTSHIELD_1_PrintString("tft lcd screen with word wrap");
    
    TFTSHIELD_1_DrawLine(50, 150, 100, 150, GREEN);
    TFTSHIELD_1_DrawLine(35, 100, 35 , 200, BLUE);
    TFTSHIELD_1_FillCircle(100,100,10,MAGENTA);
    
    TFTSHIELD_1_FillRect(150, 150, 75,75, YELLOW);
    if(touch_en)
    {
       // TFTSHIELD_1_PrintString("GO1");
    }
    //initializes touchscreen
    //clock must be set to 1MHZ when polling the touchscreen..
    Clock_1_SetDividerValue(24);
    CyDelay(10);
    
    //int touchon = 0;
    if(TFTSHIELD_1_StartTouch())
    {
         //touchon = 1;  
        Clock_1_SetDividerValue(1);
        CyDelay(1);
        //TFTSHIELD_1_PrintString("     GO2");
        Clock_1_SetDividerValue(24);
    } 
    
    
    
    for(;;)
    {
        Clock_1_SetDividerValue(24);
        //Clock_1_SetDividerValue(24);
        CyDelay(1);
        if(TFTSHIELD_1_Touched())
        {
            Clock_1_SetDividerValue(1);
            CyDelay(1);
            TFTSHIELD_1_FillRect(0, 0, 240,50, BLACK);
            TFTSHIELD_1_SetCursor(0,5);
            
            Clock_1_SetDividerValue(24);
           
            TFTSHIELD_1_ReadData(&x,&y,&z);
            x = mapCoor(x, TS_MINX, TS_MAXX, 0, 240);
            y = mapCoor(y, TS_MINY, TS_MAXY, 0, 320);
            sprintf(buffer,"x,y: %i    %i",x,y);
            Clock_1_SetDividerValue(1);
            CyDelay(1);
            TFTSHIELD_1_PrintString(buffer);
            CyDelay(1);
                
            Clock_1_SetDividerValue(24);
        }
        TFTSHIELD_1_WriteRegister8(STMPE_INT_STA, 0xFF); // reset all ints
        TFTSHIELD_1_ResetBuffer();
        
            //TFTSHIELD_1_FillRect(150, 150, 75,75, GREEN); 
           
      // }
      // else
       //{
         //  TFTSHIELD_1_FillRect(150, 150, 75,75, RED); 
      // }
        CyDelay(10);
    }
}

long mapCoor(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/* [] END OF FILE */
