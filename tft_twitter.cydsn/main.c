/*******************************************************************************
* \file main.c
* \brief This file is used for the tft_twitter project. It listens on a UART and sends the input to the TFT screen.
*
* Version 1.0
*
* \author Robert Barron
*
* \bug Sometimes adds an extra space to text in random places. This is likely an underlying problem with the TFTSHIELD component.
*******************************************************************************/

#include <device.h>

int main()
{   
    char ch[1];       /* Data received from the Serial port */
    int count = 0;

    CyGlobalIntEnable; /* Enable all interrupts by the processor. */

    TFTSHIELD_1_Start();
    UART_1_Start();
    TFTSHIELD_1_FillScreen(BLACK);
    TFTSHIELD_1_SetCursor(0,0);
    TFTSHIELD_1_SetTextColor(WHITE);  
    TFTSHIELD_1_SetTextSize(2);
    TFTSHIELD_1_SetRotation(1);
    
    //will hold the contents of a tweet plus any extra needed characters
    char tweet[200];
    
    while(1)
    {
        // Check the UART status
        //get all available chars
        ch[0] = UART_1_GetChar();
        
        //string has not been initialized
        if(ch[0] != 0 && count == 0)
        {
            strcpy(tweet,ch);
            count++;
        }
        else if(ch[0] != 0)//str cat to string
        {
            strcat(tweet,ch);
            //count++;
        }
        //if ch = 0, no chars available. print the string
        if(ch[0] == 0 && count > 0)
        {
            TFTSHIELD_1_PrintString(tweet);
            //clear the string
            memset(&tweet[0], 0, sizeof(tweet));
            count = 0;
        }
    }
    return 0;   
}


/* [] END OF FILE */
