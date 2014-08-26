/*******************************************************************************
* File Name: main.c
*
* Version: 1.10
*
* Description:
*  This project demonstrates the UART communication mechanism. 
*  Data typed on the HyperTerminal is sent through serial port to the DVK and 
*  displayed on the LCD. After that this data is sent back and displayed on the 
*  HyperTerminal.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <device.h>

#define LCD_NUM_COLUMNS (16u)

void main()
{   
    uint8 ch;
    uint8 count;
    uint8 pos;

    /* Initialize variables */
    count = 0u; /* Number of send characters   */
    pos   = 0u; /* LCD position to output into */
            
    UART_Start(); /* Start SCB UART TX+RX operation */
    
    /* Start LCD operation and output information */
    LCD_Start(); 
    LCD_ClearDisplay();

    for(;;)
    {
        /* Get received character or zero if nothing has been received yet */
        ch = UART_UartGetChar(); 

        if(0u != ch)
        {
            count++; /* Increment number of characters that were sent */
            
            if(0u == (count % LCD_NUM_COLUMNS))
            {
                /* Reach end of LCD. Clear it and start ouput from begin */
                pos = 0u;
                LCD_Position(0u, 0u);
                LCD_PrintString("                ");
            }

            /* Output sent character on LCD */
            LCD_Position(0u, pos);
            LCD_PutChar(ch);
            pos++; /* Output sent character in the next LCD position */
                    
            /* Output number of send characters */
            LCD_Position(1u, 0u);
            LCD_PrintNumber(count);
                        
            /* 
            * Send the data through UART. This functions is blocking and waits until
            * there is an entry into the TX FIFO.
            */
            UART_UartPutChar(ch);
        }
    }
}


/* [] END OF FILE */
