/*******************************************************************************
* File Name: dc.h  
* Version 1.90
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_dc_H) /* Pins dc_H */
#define CY_PINS_dc_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "dc_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 dc__PORT == 15 && ((dc__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    dc_Write(uint8 value) ;
void    dc_SetDriveMode(uint8 mode) ;
uint8   dc_ReadDataReg(void) ;
uint8   dc_Read(void) ;
uint8   dc_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define dc_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define dc_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define dc_DM_RES_UP          PIN_DM_RES_UP
#define dc_DM_RES_DWN         PIN_DM_RES_DWN
#define dc_DM_OD_LO           PIN_DM_OD_LO
#define dc_DM_OD_HI           PIN_DM_OD_HI
#define dc_DM_STRONG          PIN_DM_STRONG
#define dc_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define dc_MASK               dc__MASK
#define dc_SHIFT              dc__SHIFT
#define dc_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define dc_PS                     (* (reg8 *) dc__PS)
/* Data Register */
#define dc_DR                     (* (reg8 *) dc__DR)
/* Port Number */
#define dc_PRT_NUM                (* (reg8 *) dc__PRT) 
/* Connect to Analog Globals */                                                  
#define dc_AG                     (* (reg8 *) dc__AG)                       
/* Analog MUX bux enable */
#define dc_AMUX                   (* (reg8 *) dc__AMUX) 
/* Bidirectional Enable */                                                        
#define dc_BIE                    (* (reg8 *) dc__BIE)
/* Bit-mask for Aliased Register Access */
#define dc_BIT_MASK               (* (reg8 *) dc__BIT_MASK)
/* Bypass Enable */
#define dc_BYP                    (* (reg8 *) dc__BYP)
/* Port wide control signals */                                                   
#define dc_CTL                    (* (reg8 *) dc__CTL)
/* Drive Modes */
#define dc_DM0                    (* (reg8 *) dc__DM0) 
#define dc_DM1                    (* (reg8 *) dc__DM1)
#define dc_DM2                    (* (reg8 *) dc__DM2) 
/* Input Buffer Disable Override */
#define dc_INP_DIS                (* (reg8 *) dc__INP_DIS)
/* LCD Common or Segment Drive */
#define dc_LCD_COM_SEG            (* (reg8 *) dc__LCD_COM_SEG)
/* Enable Segment LCD */
#define dc_LCD_EN                 (* (reg8 *) dc__LCD_EN)
/* Slew Rate Control */
#define dc_SLW                    (* (reg8 *) dc__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define dc_PRTDSI__CAPS_SEL       (* (reg8 *) dc__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define dc_PRTDSI__DBL_SYNC_IN    (* (reg8 *) dc__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define dc_PRTDSI__OE_SEL0        (* (reg8 *) dc__PRTDSI__OE_SEL0) 
#define dc_PRTDSI__OE_SEL1        (* (reg8 *) dc__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define dc_PRTDSI__OUT_SEL0       (* (reg8 *) dc__PRTDSI__OUT_SEL0) 
#define dc_PRTDSI__OUT_SEL1       (* (reg8 *) dc__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define dc_PRTDSI__SYNC_OUT       (* (reg8 *) dc__PRTDSI__SYNC_OUT) 


#if defined(dc__INTSTAT)  /* Interrupt Registers */

    #define dc_INTSTAT                (* (reg8 *) dc__INTSTAT)
    #define dc_SNAP                   (* (reg8 *) dc__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_dc_H */


/* [] END OF FILE */
