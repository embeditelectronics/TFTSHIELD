/*******************************************************************************
* File Name: mosi.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "mosi.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 mosi__PORT == 15 && ((mosi__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: mosi_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None
*  
*******************************************************************************/
void mosi_Write(uint8 value) 
{
    uint8 staticBits = (mosi_DR & (uint8)(~mosi_MASK));
    mosi_DR = staticBits | ((uint8)(value << mosi_SHIFT) & mosi_MASK);
}


/*******************************************************************************
* Function Name: mosi_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void mosi_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(mosi_0, mode);
}


/*******************************************************************************
* Function Name: mosi_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro mosi_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 mosi_Read(void) 
{
    return (mosi_PS & mosi_MASK) >> mosi_SHIFT;
}


/*******************************************************************************
* Function Name: mosi_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 mosi_ReadDataReg(void) 
{
    return (mosi_DR & mosi_MASK) >> mosi_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(mosi_INTSTAT) 

    /*******************************************************************************
    * Function Name: mosi_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 mosi_ClearInterrupt(void) 
    {
        return (mosi_INTSTAT & mosi_MASK) >> mosi_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
