/*******************************************************************************
* \file main.c
* \brief This file is used to demonstrate the TFTSHIELD API for RPiSoC/PSoC. It mimics the functionality of the touchpaint program from Adafruit
*
* Version 1.0
*
* \author Robert Barron
*
* \bug 
*
* Here is the original credit:
*
*  This is our touchscreen painting example for the Adafruit ILI9341 Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
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
   // make the color selection boxes
    TFTSHIELD_1_FillRect(0, 0, BOXSIZE, BOXSIZE,RED);
    TFTSHIELD_1_FillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
    TFTSHIELD_1_FillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, GREEN);
    TFTSHIELD_1_FillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, CYAN);
    TFTSHIELD_1_FillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, BLUE);
    TFTSHIELD_1_FillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, MAGENTA);
 
  // select the current color 'red'
  TFTSHIELD_1_FillRect(0, 0, BOXSIZE, BOXSIZE,WHITE);
  currentcolor = RED;
    
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
            if (y < BOXSIZE) {
                 oldcolor = currentcolor;

                 if (x < BOXSIZE) 
                 { 
                   currentcolor = RED; 
                   TFTSHIELD_1_DrawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
                 } else if (x < BOXSIZE*2) {
                   currentcolor = YELLOW;
                   TFTSHIELD_1_DrawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, WHITE);
                 } else if (x < BOXSIZE*3) {
                   currentcolor = GREEN;
                   TFTSHIELD_1_DrawRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, WHITE);
                 } else if (x < BOXSIZE*4) {
                   currentcolor = CYAN;
                   TFTSHIELD_1_DrawRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, WHITE);
                 } else if (x < BOXSIZE*5) {
                   currentcolor = BLUE;
                   TFTSHIELD_1_DrawRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE,WHITE);
                 } else if (x < BOXSIZE*6) {
                   currentcolor = MAGENTA;
                   TFTSHIELD_1_DrawRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, WHITE);
                 }

                 if (oldcolor != currentcolor) 
                {
                    if (oldcolor == RED) 
                      TFTSHIELD_1_FillRect(0, 0, BOXSIZE, BOXSIZE, RED);
                    if (oldcolor == YELLOW) 
                      TFTSHIELD_1_FillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
                    if (oldcolor == GREEN) 
                      TFTSHIELD_1_FillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, GREEN);
                    if (oldcolor == CYAN) 
                      TFTSHIELD_1_FillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, CYAN);
                    if (oldcolor == BLUE) 
                      TFTSHIELD_1_FillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, BLUE);
                    if (oldcolor == MAGENTA) 
                      TFTSHIELD_1_FillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, MAGENTA);
                }
              }
            if (((y-PENRADIUS) > BOXSIZE) && ((y+PENRADIUS) < 320))
            {
                TFTSHIELD_1_FillCircle(x, y, PENRADIUS, currentcolor);
            }
        
        }   
    }
}

long mapCoor(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/* [] END OF FILE */
