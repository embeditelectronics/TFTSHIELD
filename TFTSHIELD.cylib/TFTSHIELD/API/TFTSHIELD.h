/**
* \file TFTSHIELD.h
*
* \brief This file contains the function prototypes and constants used in
*   the TFTSHIELD component.
*
* Version 1.0
*
* \author Robert Barron
*
* \bug No known bugs
*
* Copyright RPI Design Lab, 2014
* All Rights Reserved
* UNPUBLISHED, LICENSED SOFTWARE.
*
* CONFIDENTIAL AND PROPRIETARY INFORMATION
* WHICH IS THE PROPERTY OF the RPI Design Lab.
*
*/

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if !defined (`$INSTANCE_NAME`_H)
#define `$INSTANCE_NAME`

/***************************************
*        Function Prototypes
***************************************/    

void `$INSTANCE_NAME`_DC_LOW(void);
void `$INSTANCE_NAME`_DC_HIGH(void);
void `$INSTANCE_NAME`_CS_LOW(void);
void `$INSTANCE_NAME`_CS_HIGH(void); 
void `$INSTANCE_NAME`_Start(void);
void `$INSTANCE_NAME`_SetPixel(uint16 Pos_X, uint16 Pos_Y, uint16 Color);
void `$INSTANCE_NAME`_GotoXY(uint16 Pos_X, uint16 Pos_Y);
void `$INSTANCE_NAME`_SetPage(uint16 Start_Page, uint16 End_Page);
void `$INSTANCE_NAME`_SetAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1,
 uint16_t y1);
void `$INSTANCE_NAME`_FillRect(int16_t x, int16_t y, int16_t w, int16_t h,
  uint16_t color);
void `$INSTANCE_NAME`_FillScreen(uint16_t color);
void `$INSTANCE_NAME`_SetCol(uint16 Start_Col, uint16 End_Col);
void `$INSTANCE_NAME`_SendData16(uint16 Data16);
void `$INSTANCE_NAME`_SendData(uint8 dat);
void `$INSTANCE_NAME`_SendCmd(uint8 cmd);
void `$INSTANCE_NAME`_SPITransfer(uint8 SPIData);
void `$INSTANCE_NAME`_DrawVLine(uint16 Pos_X, uint16 Pos_Y, uint16 Length, uint16 Color);
void `$INSTANCE_NAME`_DrawLine( uint16 x1, uint16 y1, uint16 x2, uint16 y2, uint16 Color );
void `$INSTANCE_NAME`_Write(uint8_t c);
void `$INSTANCE_NAME`_DrawChar(int16_t x, int16_t y, unsigned char c,
			    uint16_t color, uint16_t bg, uint8_t size);
void `$INSTANCE_NAME`_SetCursor(int16_t x, int16_t y);
void `$INSTANCE_NAME`_SetTextSize(uint8_t s);
void `$INSTANCE_NAME`_SetTextColor(uint16_t c);
void `$INSTANCE_NAME`_SetTextWrap(uint8_t w);
void `$INSTANCE_NAME`_Print(char8 const string[]);
void `$INSTANCE_NAME`_PrintString(char8 string[]);
void `$INSTANCE_NAME`_SetRotation(uint8_t r);
uint16_t `$INSTANCE_NAME`_Color565(uint8_t r, uint8_t g, uint8_t b);

/**************************************
*           Global Variables
**************************************/

int16_t cursor_x; /**< X coordinate of text cursor */
int16_t cursor_y; /**< Y coordinate of text cursor */
uint16_t textcolor; /**< Color of text */
uint16_t textbgcolor; /**< Color of background */
uint8_t textsize; /**< Size of text */
uint8_t rotation; /**< Rotation of screen */
uint8_t wrap; /**< Text wrap setting */
int _width;
int _height;

/**************************************
*           API Constants
**************************************/

/* adafruit/seeedstudio tft shield v2 has a resolution of 320x240 */
#define TFTWIDTH  240 /**< Width of TFT in pixels */
#define TFTHEIGHT 320 /**< Height of TFT in pixels */

//ILI9341 contants
#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_RGB 0x00
#define MADCTL_BGR 0x08
#define MADCTL_MH  0x04
#define ILI9341_MADCTL  0x36


/*Basic Colors*/
#define RED		0xf800
#define GREEN	0x07e0
#define BLUE	0x001f
#define BLACK	0x0000
#define YELLOW	0xffe0
#define WHITE	0xffff
#define OFFSET 120
#define ROW 320
#define COLUMN 240

#define pi 3.14


/* [] END OF FILE */

#endif
