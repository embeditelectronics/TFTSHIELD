/*******************************************************************************
* File Name: Seven_Segment_Register.c  
* Version 1.80
*
* Description:
*  This file contains API to enable firmware to read the value of a Status 
*  Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Seven_Segment_Register.h"

#if !defined(Seven_Segment_Register_sts_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: Seven_Segment_Register_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The current value in the Status Register.
*
*******************************************************************************/
uint8 Seven_Segment_Register_Read(void) 
{ 
    return Seven_Segment_Register_Status;
}


/*******************************************************************************
* Function Name: Seven_Segment_Register_InterruptEnable
********************************************************************************
*
* Summary:
*  Enables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Seven_Segment_Register_InterruptEnable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    Seven_Segment_Register_Status_Aux_Ctrl |= Seven_Segment_Register_STATUS_INTR_ENBL;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: Seven_Segment_Register_InterruptDisable
********************************************************************************
*
* Summary:
*  Disables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Seven_Segment_Register_InterruptDisable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    Seven_Segment_Register_Status_Aux_Ctrl &= (uint8)(~Seven_Segment_Register_STATUS_INTR_ENBL);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: Seven_Segment_Register_WriteMask
********************************************************************************
*
* Summary:
*  Writes the current mask value assigned to the Status Register.
*
* Parameters:
*  mask:  Value to write into the mask register.
*
* Return:
*  None.
*
*******************************************************************************/
void Seven_Segment_Register_WriteMask(uint8 mask) 
{
    #if(Seven_Segment_Register_INPUTS < 8u)
    	mask &= (uint8)((((uint8)1u) << Seven_Segment_Register_INPUTS) - 1u);
	#endif /* End Seven_Segment_Register_INPUTS < 8u */
    Seven_Segment_Register_Status_Mask = mask;
}


/*******************************************************************************
* Function Name: Seven_Segment_Register_ReadMask
********************************************************************************
*
* Summary:
*  Reads the current interrupt mask assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The value of the interrupt mask of the Status Register.
*
*******************************************************************************/
uint8 Seven_Segment_Register_ReadMask(void) 
{
    return Seven_Segment_Register_Status_Mask;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
