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
// Size of the color selection boxes and the paintbrush size
#define BOXSIZE 40
#define PENRADIUS 3
int oldcolor, currentcolor;

long mapCoor(long x, long in_min, long in_max, long out_min, long out_max);


int main()
{   
    //initializes tft
    CyDelay(1000);
    Clock_1_SetDividerValue(24);
    CyDelay(10);
    //TFTSHIELD_1_StartTouch();
    bool touch_en = 0;
    
    if(TFTSHIELD_1_StartTouch())
    {
       touch_en = 1;
    }
    
    Clock_1_SetDividerValue(1);
    CyDelay(10);
    TFTSHIELD_1_Start();
    
    TFTSHIELD_1_FillScreen(BLACK);
    //start at 0,0 for text
    TFTSHIELD_1_SetCursor(0,0);
    TFTSHIELD_1_SetTextColor(WHITE);  
    TFTSHIELD_1_SetTextSize(2);
    
    //landscape orientation
    //TFTSHIELD_1_SetRotation(1);
    //TFTSHIELD_1_PrintString("tft lcd screen with word wrap working blah blah blah");
    
    //TFTSHIELD_1_DrawLine(50, 150, 100, 150, GREEN);
   // TFTSHIELD_1_DrawLine(35, 100, 35 , 200, BLUE);
    //TFTSHIELD_1_FillCircle(100,100,10,MAGENTA);
    
    //TFTSHIELD_1_FillRect(150, 150, 75,75, YELLOW);
    if(touch_en)
    {
        //TFTSHIELD_1_PrintString("GO1");
    }
    //initializes touchscreen
    //clock must be set to 1MHZ when polling the touchscreen..
    Clock_1_SetDividerValue(24);
    CyDelay(10);
    
    //int touchon = 0;
    if(TFTSHIELD_1_StartTouch())
    {
         //touchon = 1;  
        /*Clock_1_SetDividerValue(1);
        CyDelay(1);
        TFTSHIELD_1_PrintString("     GO2");
        Clock_1_SetDividerValue(24);*/
    }
    
    Clock_1_SetDividerValue(1);
    CyDelay(10);
    
    //leds
    TFTSHIELD_1_FillCircle(120,40,20,GRAY);
    TFTSHIELD_1_FillCircle(120,120,20,GRAY);
    TFTSHIELD_1_FillCircle(120,200,20,GRAY);
    TFTSHIELD_1_FillCircle(120,280,20,GRAY);
    
    //pushbuttons
    TFTSHIELD_1_FillRect(175,15,50,50,GRAY);
    TFTSHIELD_1_FillRect(175,95,50,50,GRAY);
    TFTSHIELD_1_FillRect(175,175,50,50,GRAY);
    TFTSHIELD_1_FillRect(175,255,50,50,GRAY);
    TFTSHIELD_1_FillCircle(200,40,20,BLACK);
    TFTSHIELD_1_FillCircle(200,120,20,BLACK);
    TFTSHIELD_1_FillCircle(200,200,20,BLACK);
    TFTSHIELD_1_FillCircle(200,280,20,BLACK);
    
    for(;;)
    {
        Clock_1_SetDividerValue(24);
        uint16_t x, y;
        uint8_t z, buf;
        char buffer[50];
        //Clock_1_SetDividerValue(24);
        CyDelay(1);
        if(TFTSHIELD_1_Touched())
        {
           
            TFTSHIELD_1_ReadData(&x,&y,&z);
            x = mapCoor(x, TS_MINX, TS_MAXX, 0, 240);
            y = mapCoor(y, TS_MINY, TS_MAXY, 0, 320);
            Clock_1_SetDividerValue(1);
            if(x > 175 && x < 225)
            {
                if(y > 15 && y < 65)
                {
                    TFTSHIELD_1_FillCircle(120,40,20,RED);
                }
                else
                {
                    TFTSHIELD_1_FillCircle(120,40,20,GRAY);
                }
                 if(y > 95 && y < 145)
                {
                    TFTSHIELD_1_FillCircle(120,120,20,RED);
                }
                else
                {
                    TFTSHIELD_1_FillCircle(120,120,20,GRAY);
                 }
                 if(y > 175 && y < 225)
                {
                    TFTSHIELD_1_FillCircle(120,200,20,RED);
                }
                else
                {
                    TFTSHIELD_1_FillCircle(120,200,20,GRAY);
                 }
                  if(y > 255 && y < 295)
                {
                    TFTSHIELD_1_FillCircle(120,280,20,RED);
                }
                
                else
                {
                     TFTSHIELD_1_FillCircle(120,280,20,GRAY);
                 }
                
            }
            else
            {
            TFTSHIELD_1_FillCircle(120,40,20,GRAY);
            TFTSHIELD_1_FillCircle(120,120,20,GRAY);
            TFTSHIELD_1_FillCircle(120,200,20,GRAY);
            TFTSHIELD_1_FillCircle(120,280,20,GRAY);
            }
        }
        else
        {
            TFTSHIELD_1_ResetBuffer();
             Clock_1_SetDividerValue(1);
            //leds
            TFTSHIELD_1_FillCircle(120,40,20,GRAY);
            TFTSHIELD_1_FillCircle(120,120,20,GRAY);
            TFTSHIELD_1_FillCircle(120,200,20,GRAY);
            TFTSHIELD_1_FillCircle(120,280,20,GRAY);
        }
    
    }
    
    
}

long mapCoor(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}