/*******************************************************************************
* \file main.c
* \brief This program generates functionality for TFT shield to be used as an input/output device for digital logic.
*
* Version 1.0
*
* \author Brian Bradley
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

#define x_max 240
#define y_max 320 //screen resolution
#define top_space 25
#define push_buttons 4
#define LEDs 4
#define switches 4
#define HEX 1

long mapCoor(long x, long in_min, long in_max, long out_min, long out_max);
void DrawPushbutton(int i);
void DrawLED(int i, int state);
int InputTouched(); // -1 if PB not touched 0 for first PB
void TFT_INIT();
void DrawSlideSwitch(int i, int state);
void DrawHex(int i, uint8 stat);
void DrawHEX_a(int i, uint8 state);
void DrawHEX_b(int i, uint8 state);
void DrawHEX_c(int i, uint8 state);
void DrawHEX_d(int i, uint8 state);
void DrawHEX_e(int i, uint8 state);
void DrawHEX_f(int i, uint8 state);
void DrawHEX_g(int i, uint8 state);
void DrawInputs();
void DrawOutputs();
//int EditLayout();
void waiting();

int main()
{   
    TFT_INIT();
    int SW_state[] = {-1,-1,-1,-1,-1,-1,-1,-1};//init data vessel for Switch states
    TFTSHIELD_1_FillRoundRect(0, 0, 25, 320, 5, RED);//Filling the top for menu access
    
   // int Data=EditLayout();
    DrawInputs();
    DrawOutputs();
   
    for(;;) //program loop
    {  int i =0;
       int SW_state_prev[8];
       for (i = 0 ; i<8 ; i++){SW_state_prev[i]=SW_state[i];}
       //for (i = switches; i < switches + push_buttons; i++){DrawLED(i,0);} 
       PushButton_Register_Write(0x00);//clear PB states

       int touched = InputTouched(); //returns which input was touched, -1 for none, 0 for first input
       if (touched>=0 && touched<switches){SW_state[touched]*=-1;}//switch hit
       else if (touched>=switches){PushButton_Register_Write(0x01<<(touched - switches));}//PB hit
      
       for (i=0 ; i<switches ; i++) //writing to switches
        {
        if (SW_state[i]!=SW_state_prev[i])
            {   
                uint16 sw_stat;
                uint16 new_sw_stat;
                uint16 mask_h;
                uint16 mask_l = 0x01;
                
                sw_stat = Switch_Register_Read();
                char buffer[50];
              
            
                if (SW_state[i] == -1)
                {   DrawSlideSwitch(i, -1);
                    mask_h=0xFF<<(i+1);
                    int k =0;
                    if (i!=0){for(k = 1 ; k<i ; k++){mask_l|=(0x01<<k);}}
                    else {mask_l = 0x00;}
                    uint16 mask = mask_h | mask_l;
                    new_sw_stat = sw_stat&mask;
                }
                
                else if (SW_state[i] == 1)
                {
                    DrawSlideSwitch(i, 1);
                    new_sw_stat = (sw_stat) | (0x01 << i);
                }
                
                Switch_Register_Write(new_sw_stat);
                waiting();
                
            }
            
             
        }
        
        uint16 LED_stat = LED_Register_Read();
        uint16 prev_LED_stat;   
        
        
        for (i = 0 ; i< LEDs ; i++)
            {
              uint8 LED_i_state = LED_stat&(0x01<<i);
              uint8 prev_LED_i_stat = prev_LED_stat&(0x01<<i);
              if (LED_i_state!=0 && prev_LED_i_stat == 0){DrawLED(i+HEX, 1);}
              else if (LED_i_state == 0 && prev_LED_i_stat !=0){DrawLED(i+HEX, 0);}
            }
         prev_LED_stat = LED_stat;   
         
        uint16 prev_hex_stat;
        uint16 hex_stat = Seven_Segment_Register_Read();
        if (hex_stat!=prev_hex_stat){DrawHex(0, hex_stat);}
        prev_hex_stat = hex_stat;
        
       
    } 
 }
 

void DrawPushbutton(int i)
{
    int separation_PB;
    int inputs = switches + push_buttons;
    
    if (inputs>0){separation_PB = y_max/inputs;}//check for div by zero 
    else{separation_PB = y_max + 1;}
    
    int width_PB = separation_PB/2; //forcing width to be the same as width of the switches.
    int length_PB = width_PB;
    
    if (length_PB>x_max/2.5 - top_space )
    {   
        length_PB = x_max/2.5 - top_space;
        width_PB = length_PB;
        separation_PB = 2*width_PB;
    }
    
    int empty_PB =y_max/(inputs+1) - width_PB/2;
    //needs to start drawing so it is centered with switches, length of switch is twice length of PB
    int x_PB = x_max - 2.5*length_PB;
 
    TFTSHIELD_1_FillRect(x_PB, (i+1)*empty_PB + i*width_PB/2, length_PB, width_PB, GRAY);
    
    int center_PB_x = x_PB + length_PB/2;
    int radius_PB = (width_PB*0.75)/2;
    int center_PB_y = (i+1)*empty_PB + (i+1)*width_PB/2;
    TFTSHIELD_1_FillCircle(center_PB_x, center_PB_y, radius_PB, BLACK);
}
void waiting()//if the TFT is touched, wait until it is released.
{
    Clock_1_SetDividerValue(24);//Clock division needed for touch
    if (TFTSHIELD_1_Touched()){while (TFTSHIELD_1_Touched()){}} //waiting until PB is released
    Clock_1_SetDividerValue(1);//reset clock divider
}
void DrawSlideSwitch(int i, int state)
{
    // slideswitches
    int separation_SW;
    int inputs = switches + push_buttons;
    
    if (inputs > 0){ separation_SW = y_max/inputs;} // check for division by zero
    else {separation_SW = y_max + 1;}
    
    int width_SW = separation_SW/2;
    int length_SW = width_SW*2;
    if (length_SW>x_max/2.5 - top_space )
    {   
        length_SW = x_max/2.5 - top_space;
        width_SW = length_SW/2;
        separation_SW = 2*width_SW;
    }
    
    int empty_SW =y_max/(inputs+1) - width_SW/2;
    int x_SW = x_max - 1.5*length_SW;
 
    TFTSHIELD_1_FillRoundRect(x_SW, (i+1)*empty_SW + i*width_SW/2, length_SW, width_SW, width_SW/4, GRAY);
    
    if (state == 1) //turning on animation
    {
    int k = 0;
    while (k < .85*length_SW/2 )
    {
    TFTSHIELD_1_FillRoundRect(x_SW + ((.15*length_SW)/2), (i+1)*empty_SW + i*width_SW/2 + (.15*width_SW)/2, length_SW*.85, width_SW*.85, (width_SW*.85)/4, BLACK);
    TFTSHIELD_1_FillRoundRect(x_SW + ((.15*length_SW)/2) + (.85*length_SW/2) - k,  (i+1)*empty_SW + i*width_SW/2 + (.15*width_SW)/2, (length_SW*.85)/2, width_SW*.85, (width_SW*.85)/4, WHITE);
    TFTSHIELD_1_DrawRoundRect(x_SW + ((.15*length_SW)/2) + (.85*length_SW/2) - k, (i+1)*empty_SW + i*width_SW/2 + (.15*width_SW)/2, (length_SW*.85)/2, width_SW*.85, (width_SW*.85)/4, BLACK);
    k = k + (.85*length_SW/2)/2;
    }
  
    TFTSHIELD_1_FillRoundRect(x_SW + ((.15*length_SW)/2), (i+1)*empty_SW + i*width_SW/2 + (.15*width_SW)/2, length_SW*.85, width_SW*.85, (width_SW*.85)/4, GREEN);
    TFTSHIELD_1_FillRoundRect(x_SW + ((.15*length_SW)/2), (i+1)*empty_SW + i*width_SW/2 + (.15*width_SW)/2, (length_SW*.85)/2, width_SW*.85, (width_SW*.85)/4, WHITE);
    TFTSHIELD_1_DrawRoundRect(x_SW + ((.15*length_SW)/2), (i+1)*empty_SW + i*width_SW/2 + (.15*width_SW)/2, (length_SW*.85)/2, width_SW*.85, (width_SW*.85)/4, BLACK);
    }
    
    
    else if (state == -1)//turning off animation
    {
        int k = 0;
        while (k<(.85*length_SW/2))
    {
    TFTSHIELD_1_FillRoundRect(x_SW + ((.15*length_SW)/2), (i+1)*empty_SW + i*width_SW/2 + (.15*width_SW)/2, length_SW*.85, width_SW*.85, (width_SW*.85)/4, GREEN);
    TFTSHIELD_1_FillRoundRect(x_SW + ((.15*length_SW)/2) + k, (i+1)*empty_SW + i*width_SW/2 + (.15*width_SW)/2, (length_SW*.85)/2, width_SW*.85, (width_SW*.85)/4, WHITE);
    TFTSHIELD_1_DrawRoundRect(x_SW + ((.15*length_SW)/2) + k, (i+1)*empty_SW + i*width_SW/2 + (.15*width_SW)/2, (length_SW*.85)/2, width_SW*.85, (width_SW*.85)/4, BLACK);
    k = k+ (.85*length_SW/2)/2;
    
    }
    
     
    TFTSHIELD_1_FillRoundRect(x_SW + ((.15*length_SW)/2), (i+1)*empty_SW + i*width_SW/2 + (.15*width_SW)/2, length_SW*.85, width_SW*.85, (width_SW*.85)/4, BLACK);
    TFTSHIELD_1_FillRoundRect(x_SW + ((.15*length_SW)/2) + (.85*length_SW/2), (i+1)*empty_SW + i*width_SW/2 + (.15*width_SW)/2, (length_SW*.85)/2, width_SW*.85, (width_SW*.85)/4, WHITE);
    TFTSHIELD_1_DrawRoundRect(x_SW + ((.15*length_SW)/2) + (.85*length_SW/2), (i+1)*empty_SW + i*width_SW/2 + (.15*width_SW)/2, (length_SW*.85)/2, width_SW*.85, (width_SW*.85)/4, BLACK);
    k = k+ (.85*length_SW/2)/2;
    }
    
}

void DrawLED(int i, int state)
{
    uint16 color ;
    
    if (state == 0){color = GRAY;}
    else if (state == 1){color = RED;}
    
    int outputs = LEDs + HEX;
    int separation_LED;
    
    if (outputs>0){separation_LED = y_max/outputs;}
    else          {separation_LED = y_max + 1;}
   
    int size_LED = separation_LED/2;
    
    if (size_LED > x_max/2.5 - top_space){size_LED = x_max/2.5 - top_space;}
    
    int empty_LED = (separation_LED - size_LED)/2;
    int x_LED = top_space + .75*separation_LED;
    int center_LED_x = x_LED + size_LED/2;
    int radius_LED = (size_LED*0.75)/2;
    int center_LED_y = empty_LED + i*separation_LED + size_LED/2;
    
    TFTSHIELD_1_FillCircle(center_LED_x, center_LED_y, radius_LED, color);
}
void DrawHEX_a(int i, uint8 state)
{
    uint16 color ;
    int separation_HEX;
    int outputs = HEX + LEDs;
    
    if (outputs>0){separation_HEX = y_max/outputs;}//check for div by zero
    else      {separation_HEX = y_max + 1;}
    
    int width_HEX = separation_HEX/2;
    int length_HEX = width_HEX*2;
    if (length_HEX + top_space >x_max/2.5)
    {   
        length_HEX = x_max/2.5 - top_space;
        width_HEX = length_HEX/2;
        separation_HEX = 2*width_HEX;
    }
    
    int empty_HEX =y_max /(outputs+1) - width_HEX/2;
    int x_HEX = top_space + length_HEX/2;
    
    if (state != 0){color = RED;}
    else {color = 0x0102;}
    
    TFTSHIELD_1_FillRoundRect(x_HEX + ((.20*length_HEX)/2), (i+1)*empty_HEX + i*width_HEX/2 + .45*width_HEX/2, (length_HEX*.80)/10, width_HEX*.55, (length_HEX*.80)/40, color);
}
void DrawHEX_b(int i, uint8 state)
{
    uint16 color ;
    int separation_HEX;
    int outputs = HEX + LEDs;
    
    if (outputs>0){separation_HEX = y_max/outputs;}//check for div by zero
    else      {separation_HEX = y_max + 1;}
    
    int width_HEX = separation_HEX/2;
    int length_HEX = width_HEX*2;
    if (length_HEX + top_space >x_max/2.5)
    {   
        length_HEX = x_max/2.5 - top_space;
        width_HEX = length_HEX/2;
        separation_HEX = 2*width_HEX;
    }
    
    int empty_HEX =y_max /(outputs+1) - width_HEX/2;
    int x_HEX = top_space + length_HEX/2;
    
    if (state != 0){color = RED;}
    else {color = 0x0102;}
    
    TFTSHIELD_1_FillRoundRect(x_HEX + ((.20*length_HEX)/2) + (length_HEX)/10, (i+1)*empty_HEX + i*width_HEX/2 + .35*width_HEX/2, width_HEX*.65 - (length_HEX)/10,(length_HEX*.80)/10, (length_HEX*.80)/40, color);
}
void DrawHEX_c(int i, uint8 state)
{
    uint16 color ;
    int separation_HEX;
    int outputs = HEX + LEDs;
    
    if (outputs>0){separation_HEX = y_max/outputs;}//check for div by zero
    else      {separation_HEX = y_max + 1;}
    
    int width_HEX = separation_HEX/2;
    int length_HEX = width_HEX*2;
    if (length_HEX + top_space >x_max/2.5)
    {   
        length_HEX = x_max/2.5 - top_space;
        width_HEX = length_HEX/2;
        separation_HEX = 2*width_HEX;
    }
    
    int empty_HEX =y_max /(outputs+1) - width_HEX/2;
    int x_HEX = top_space + length_HEX/2;
    
    if (state != 0){color = RED;}
    else {color = 0x0102;}
    
    TFTSHIELD_1_FillRoundRect(x_HEX + ((.20*length_HEX)/2) + (length_HEX)/10 + .70*width_HEX, (i+1)*empty_HEX + i*width_HEX/2 + .35*width_HEX/2, width_HEX*.65 - (length_HEX)/10,(length_HEX*.80)/10, (length_HEX*.80)/40, color);

}
void DrawHEX_d(int i, uint8 state)
{
    uint16 color ;
    int separation_HEX;
    int outputs = HEX + LEDs;
    
    if (outputs>0){separation_HEX = y_max/outputs;}//check for div by zero
    else      {separation_HEX = y_max + 1;}
    
    int width_HEX = separation_HEX/2;
    int length_HEX = width_HEX*2;
    if (length_HEX + top_space >x_max/2.5)
    {   
        length_HEX = x_max/2.5 - top_space;
        width_HEX = length_HEX/2;
        separation_HEX = 2*width_HEX;
    }
    
    int empty_HEX =y_max /(outputs+1) - width_HEX/2;
    int x_HEX = top_space + length_HEX/2;
    
    if (state != 0){color = RED;}
    else {color = 0x0102;}
    
    TFTSHIELD_1_FillRoundRect(x_HEX + length_HEX*.9 - ((.24*length_HEX)/2), (i+1)*empty_HEX + i*width_HEX/2 + .45*width_HEX/2, (length_HEX*.80)/10, width_HEX*.55, (length_HEX*.80)/40, color);
    
}
void DrawHEX_e(int i, uint8 state)
{
    
    uint16 color ;
    int separation_HEX;
    int outputs = HEX + LEDs;
    
    if (outputs>0){separation_HEX = y_max/outputs;}//check for div by zero
    else      {separation_HEX = y_max + 1;}
    
    int width_HEX = separation_HEX/2;
    int length_HEX = width_HEX*2;
    if (length_HEX + top_space > x_max/2.5)
    {   
        length_HEX = x_max/2.5 - top_space;
        width_HEX = length_HEX/2;
        separation_HEX = 2*width_HEX;
    }
    
    int empty_HEX = y_max/(outputs+1) - width_HEX/2;
    int x_HEX = top_space + length_HEX/2;
    
    if (state != 0){color = RED;}
    else {color = 0x0102;}
    
    TFTSHIELD_1_FillRoundRect(x_HEX + ((.20*length_HEX)/2) + (length_HEX)/10 + .70*width_HEX, (i+1)*empty_HEX + i*width_HEX/2 + .35*width_HEX/2 + .65*width_HEX - (length_HEX*.80)/10 , width_HEX*.65 - (length_HEX)/10,(length_HEX*.80)/10, (length_HEX*.80)/40, color);
}
void DrawHEX_f(int i, uint8 state)
{
    uint16 color ;
    int separation_HEX;
    int outputs = HEX + LEDs;
    
    if (outputs>0){separation_HEX = y_max/outputs;}//check for div by zero
    else      {separation_HEX = y_max + 1;}
    
    int width_HEX = separation_HEX/2;
    int length_HEX = width_HEX*2;
    if (length_HEX + top_space > x_max/2.5)
    {   
        length_HEX = x_max/2.5 - top_space;
        width_HEX = length_HEX/2;
        separation_HEX = 2*width_HEX;
    }
    
    int empty_HEX =y_max /(outputs+1) - width_HEX/2;
    int x_HEX = top_space + length_HEX/2;
    
    if (state != 0){color = RED;}
    else {color = 0x0102;}
    
    TFTSHIELD_1_FillRoundRect(x_HEX + ((.20*length_HEX)/2) + (length_HEX)/10, (i+1)*empty_HEX + i*width_HEX/2 + .35*width_HEX/2 + .65*width_HEX - (length_HEX*.80)/10, width_HEX*.65 - (length_HEX)/10,(length_HEX*.80)/10, (length_HEX*.80)/40, color);
}
void DrawHEX_g(int i, uint8 state)
{
    
    uint16 color ;
    int separation_HEX;
    int outputs = HEX + LEDs;
    
    if (outputs>0){separation_HEX = y_max/outputs;}//check for div by zero
    else      {separation_HEX = y_max + 1;}
    
    int width_HEX = separation_HEX/2;
    int length_HEX = width_HEX*2;
    if (length_HEX + top_space > x_max/2.5)
    {   
        length_HEX = x_max/2.5 - top_space;
        width_HEX = length_HEX/2;
        separation_HEX = 2*width_HEX;
    }
    
    int empty_HEX = y_max /(outputs+1) - width_HEX/2;
    int x_HEX = top_space + length_HEX/2;
    
    if (state !=0 ){color = RED;}
    else {color = 0x0102;}
    
    TFTSHIELD_1_FillRoundRect(x_HEX + ((length_HEX*45)/100) , (i+1)*empty_HEX + i*width_HEX/2 + .45*width_HEX/2, (length_HEX*.9)/10, width_HEX*.55, (length_HEX*.80)/40, color);
   
}

void DrawHex(int i, uint8 stat)
{
   
    int separation_HEX;
    int outputs = HEX + LEDs;
    
    if (outputs>0){separation_HEX = y_max/outputs;}//check for div by zero
    else      {separation_HEX = y_max + 1;}
    
    int width_HEX = separation_HEX/2;
    int length_HEX = width_HEX*2;
    
    if (length_HEX + top_space > x_max/2.5)
    {   
        length_HEX = x_max/2.5 - top_space;
        width_HEX = length_HEX/2;
        separation_HEX = 2*width_HEX;
    }
    
    int empty_HEX =y_max /(outputs+1) - width_HEX/2;
    int x_HEX = top_space + length_HEX/2;
 
    TFTSHIELD_1_FillRect(x_HEX, (i+1)*empty_HEX + i*width_HEX/2, length_HEX, width_HEX, GRAY);
    TFTSHIELD_1_FillRect(x_HEX + ((.1*length_HEX)/2), (i+1)*empty_HEX + i*width_HEX/2 + .1*width_HEX/2, length_HEX*.9, width_HEX*.9, BLACK);

    DrawHEX_a(i, stat&0x01);
    DrawHEX_b(i, stat&0x02);
    DrawHEX_c(i, stat&0x04);
    DrawHEX_d(i, stat&0x08);
    DrawHEX_e(i, stat&0x10);
    DrawHEX_f(i, stat&0x20);
    DrawHEX_g(i, stat&0x40);
    
 }
int InputTouched()
{   
    int inputs = switches + push_buttons;
    int separation;
    
    if (inputs>0){separation = y_max/inputs;} //check for div by zero
    else         {separation = y_max + 1;}
    int width = separation/2;
    int length = width*2;
    if (length>x_max/2.5)
    {   
        length = x_max/2.5;
        width = length/2;
        separation = 2*width;
    }
    
    int empty = y_max/(inputs+1) - width/2;
    int x_input = x_max - 1.5*length;
    uint16_t x, y;
    uint8_t z;
    int i = 0;
    
    Clock_1_SetDividerValue(24);
    CyDelay(1);
    
    if(TFTSHIELD_1_Touched())
    {
         TFTSHIELD_1_ReadData(&x,&y,&z);
         x = mapCoor(x, TS_MINX, TS_MAXX, 0, 240);
         y = mapCoor(y, TS_MINY, TS_MAXY, 0, 320);
        
    if(x > x_input && x < (x_max - length/2))
    {
       for (i=0; i<inputs; i++)
        {
            if (y>((i+1)*empty) && y < ((i+1)*empty + (i+1)*(width/2)))
            { 
              Clock_1_SetDividerValue(1);
              return i;//input i touched
            }
        }   
            TFTSHIELD_1_ResetBuffer();//clears and resets FIFO buffer
            Clock_1_SetDividerValue(1);
            return -1;//nothing touched
    }
    }
    
    else 
    {   
        TFTSHIELD_1_ResetBuffer();
        Clock_1_SetDividerValue(1);
        return -1;//nothing touched
    }
    
    
}
    
void TFT_INIT()
{
    CyDelay(1000);
    Clock_1_SetDividerValue(24);
    CyDelay(10);
    while(!TFTSHIELD_1_StartTouch()){}
    CyDelay(1000);
    Clock_1_SetDividerValue(1);
    CyDelay(10);
    TFTSHIELD_1_Start();
    TFTSHIELD_1_FillScreen(BLACK);
    TFTSHIELD_1_SetCursor(0,0);//start at 0,0 for text
    TFTSHIELD_1_SetTextColor(WHITE);  
    TFTSHIELD_1_SetTextSize(2);
    CyDelay(10);
    
}

long mapCoor(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void DrawInputs()
{   
    int i = 0;
    int SW_state[] = {-1,-1,-1,-1,-1,-1,-1,-1};
    
    for (i=0; i<switches; i++){DrawSlideSwitch(i, SW_state[i]);}//Draw switches
    for (i = switches ; i < (switches + push_buttons) ; i++){DrawPushbutton(i);}//Draw buttons
}

void DrawOutputs()
{   
    int i = 0;
    uint8 HEX_state = 0x00;
    
    for (i = 0 ; i<HEX ; i++){DrawHex(i, HEX_state);} //Draw HEX displays
    for (i=HEX; i<LEDs + HEX; i++){DrawLED(i, 0);} //Draw LEDs
}