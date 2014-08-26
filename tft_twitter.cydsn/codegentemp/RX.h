/*******************************************************************************
* File Name: RX.h  
* Version 2.0
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_RX_H) /* Pins RX_H */
#define CY_PINS_RX_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RX_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RX__PORT == 15 && ((RX__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    RX_Write(uint8 value) ;
void    RX_SetDriveMode(uint8 mode) ;
uint8   RX_ReadDataReg(void) ;
uint8   RX_Read(void) ;
uint8   RX_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define RX_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define RX_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define RX_DM_RES_UP          PIN_DM_RES_UP
#define RX_DM_RES_DWN         PIN_DM_RES_DWN
#define RX_DM_OD_LO           PIN_DM_OD_LO
#define RX_DM_OD_HI           PIN_DM_OD_HI
#define RX_DM_STRONG          PIN_DM_STRONG
#define RX_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define RX_MASK               RX__MASK
#define RX_SHIFT              RX__SHIFT
#define RX_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RX_PS                     (* (reg8 *) RX__PS)
/* Data Register */
#define RX_DR                     (* (reg8 *) RX__DR)
/* Port Number */
#define RX_PRT_NUM                (* (reg8 *) RX__PRT) 
/* Connect to Analog Globals */                                                  
#define RX_AG                     (* (reg8 *) RX__AG)                       
/* Analog MUX bux enable */
#define RX_AMUX                   (* (reg8 *) RX__AMUX) 
/* Bidirectional Enable */                                                        
#define RX_BIE                    (* (reg8 *) RX__BIE)
/* Bit-mask for Aliased Register Access */
#define RX_BIT_MASK               (* (reg8 *) RX__BIT_MASK)
/* Bypass Enable */
#define RX_BYP                    (* (reg8 *) RX__BYP)
/* Port wide control signals */                                                   
#define RX_CTL                    (* (reg8 *) RX__CTL)
/* Drive Modes */
#define RX_DM0                    (* (reg8 *) RX__DM0) 
#define RX_DM1                    (* (reg8 *) RX__DM1)
#define RX_DM2                    (* (reg8 *) RX__DM2) 
/* Input Buffer Disable Override */
#define RX_INP_DIS                (* (reg8 *) RX__INP_DIS)
/* LCD Common or Segment Drive */
#define RX_LCD_COM_SEG            (* (reg8 *) RX__LCD_COM_SEG)
/* Enable Segment LCD */
#define RX_LCD_EN                 (* (reg8 *) RX__LCD_EN)
/* Slew Rate Control */
#define RX_SLW                    (* (reg8 *) RX__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RX_PRTDSI__CAPS_SEL       (* (reg8 *) RX__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RX_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RX__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RX_PRTDSI__OE_SEL0        (* (reg8 *) RX__PRTDSI__OE_SEL0) 
#define RX_PRTDSI__OE_SEL1        (* (reg8 *) RX__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RX_PRTDSI__OUT_SEL0       (* (reg8 *) RX__PRTDSI__OUT_SEL0) 
#define RX_PRTDSI__OUT_SEL1       (* (reg8 *) RX__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RX_PRTDSI__SYNC_OUT       (* (reg8 *) RX__PRTDSI__SYNC_OUT) 


#if defined(RX__INTSTAT)  /* Interrupt Registers */

    #define RX_INTSTAT                (* (reg8 *) RX__INTSTAT)
    #define RX_SNAP                   (* (reg8 *) RX__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RX_H */


/* [] END OF FILE */
