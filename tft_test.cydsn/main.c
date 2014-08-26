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
int main()
{   
    //initializes tft
    CyDelay(1000);
    Clock_1_SetDividerValue(24);
    CyDelay(10);
    //TFTSHIELD_1_StartTouch();
    bool touch_en = 0;
    
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
    TFTSHIELD_1_SetRotation(1);
    //TFTSHIELD_1_PrintString("tft lcd screen with word wrap working blah blah blah");
    
    TFTSHIELD_1_DrawLine(50, 150, 100, 150, GREEN);
    TFTSHIELD_1_DrawLine(35, 100, 35 , 200, BLUE);
    TFTSHIELD_1_FillCircle(100,100,10,MAGENTA);
    
    //TFTSHIELD_1_FillRect(150, 150, 75,75, YELLOW);
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
        uint16_t x, y;
        uint8_t z, buf;
        char buffer[50];
        //Clock_1_SetDividerValue(24);
        CyDelay(1);
        while(TFTSHIELD_1_Touched())
        {
            Clock_1_SetDividerValue(24);
                
            //while(!TFTSHIELD_1_BufferEmpty())
            //{
                //TFTSHIELD_1_BufferSize();
                buf = TFTSHIELD_1_BufferSize();
                z = 255;
                TFTSHIELD_1_ReadData(&x,&y,&z);
                sprintf(buffer,"x,y,z: %i    %i",buf,z);
                Clock_1_SetDividerValue(1);
                CyDelay(1);
                TFTSHIELD_1_PrintString(buffer);
                CyDelay(1);
                TFTSHIELD_1_FillRect(40, 0, 200,20, BLACK);
                TFTSHIELD_1_SetCursor(0,0);
                Clock_1_SetDividerValue(24);
                CyDelay(1);
                
                /*if(buf == 0)
                {
                    TFTSHIELD_1_WriteRegister8(STMPE_INT_STA, 0xFF); // reset all ints
                }*/
            //}
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

/* [] END OF FILE */
