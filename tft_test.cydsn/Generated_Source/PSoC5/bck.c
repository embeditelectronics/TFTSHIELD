/*******************************************************************************
* File Name: bck.c  
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
#include "bck.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 bck__PORT == 15 && ((bck__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: bck_Write
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
void bck_Write(uint8 value) 
{
    uint8 staticBits = (bck_DR & (uint8)(~bck_MASK));
    bck_DR = staticBits | ((uint8)(value << bck_SHIFT) & bck_MASK);
}


/*******************************************************************************
* Function Name: bck_SetDriveMode
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
void bck_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(bck_0, mode);
}


/*******************************************************************************
* Function Name: bck_Read
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
*  Macro bck_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 bck_Read(void) 
{
    return (bck_PS & bck_MASK) >> bck_SHIFT;
}


/*******************************************************************************
* Function Name: bck_ReadDataReg
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
uint8 bck_ReadDataReg(void) 
{
    return (bck_DR & bck_MASK) >> bck_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(bck_INTSTAT) 

    /*******************************************************************************
    * Function Name: bck_ClearInterrupt
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
    uint8 bck_ClearInterrupt(void) 
    {
        return (bck_INTSTAT & bck_MASK) >> bck_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
