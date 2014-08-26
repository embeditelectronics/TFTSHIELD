/*******************************************************************************
* File Name: Seven_Segment_Register.h  
* Version 1.80
*
* Description:
*  This file containts Status Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_STATUS_REG_Seven_Segment_Register_H) /* CY_STATUS_REG_Seven_Segment_Register_H */
#define CY_STATUS_REG_Seven_Segment_Register_H

#include "cytypes.h"
#include "CyLib.h"


/***************************************
*        Function Prototypes
***************************************/

uint8 Seven_Segment_Register_Read(void) ;
void Seven_Segment_Register_InterruptEnable(void) ;
void Seven_Segment_Register_InterruptDisable(void) ;
void Seven_Segment_Register_WriteMask(uint8 mask) ;
uint8 Seven_Segment_Register_ReadMask(void) ;


/***************************************
*           API Constants
***************************************/

#define Seven_Segment_Register_STATUS_INTR_ENBL    0x10u


/***************************************
*         Parameter Constants
***************************************/

/* Status Register Inputs */
#define Seven_Segment_Register_INPUTS              8


/***************************************
*             Registers
***************************************/

/* Status Register */
#define Seven_Segment_Register_Status             (* (reg8 *) Seven_Segment_Register_sts_sts_reg__STATUS_REG )
#define Seven_Segment_Register_Status_PTR         (  (reg8 *) Seven_Segment_Register_sts_sts_reg__STATUS_REG )
#define Seven_Segment_Register_Status_Mask        (* (reg8 *) Seven_Segment_Register_sts_sts_reg__MASK_REG )
#define Seven_Segment_Register_Status_Aux_Ctrl    (* (reg8 *) Seven_Segment_Register_sts_sts_reg__STATUS_AUX_CTL_REG )

#endif /* End CY_STATUS_REG_Seven_Segment_Register_H */


/* [] END OF FILE */
