/******************************************************************************
 *
 * Module: SysTick
 *
 * File Name: SysTick.c
 *
 * Description: Source file for the ARM Cortex M4 SysTick driver
 *
 * Author: Mohamed Hisham
 *
 *******************************************************************************/

/*******************************************************************************
 * INCLUSIONS                                                                 *
 *******************************************************************************/

#include "SysTick.h"
#include "tm4c123gh6pm_registers.h"

/*******************************************************************************
 * GLOBAL VARIABLES                                                            *
 *******************************************************************************/

static volatile void (*g_SysTickCallBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 * FUNCTION DEFINITIONS                                                        *
 *******************************************************************************/

/*********************************************************************
 * Service Name: SysTick_Init
 * Sync/Async: Asynchronous
 * Reentrancy: reentrant
 * Parameters (in): a_TimeInMilliSeconds - Time in milliseconds
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initialize the SysTick timer with the specified time in milliseconds
 * using interrupts.
 **********************************************************************/
void SysTick_Init(uint16 a_TimeInMilliSeconds) {

    if ( ((16000 * a_TimeInMilliSeconds - 1) > 0x00FFFFFF) || ((16000 * a_TimeInMilliSeconds - 1) < 0x01) ) {
        return; //Error Checking if the number of ticks is more than available in regiester
    }
    SYSTICK_CTRL_REG    = 0;              /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_RELOAD_REG  = (16000 * a_TimeInMilliSeconds) - 1 ;  /* Set the Reload value with a_TimeInMilliSeconds converted to ticks */
    SYSTICK_CURRENT_REG = 0;              /* Clear the Current Register value */
    /* Configure the SysTick Control Register
     * Enable the SysTick Timer (ENABLE = 1)
     * Enable SysTick Interrupt (INTEN = 1)
     * Choose the clock source to be System Clock (CLK_SRC = 1) */
    SYSTICK_CTRL_REG   |= SYSTICK_CTRL_ENABLE_BIT | SYSTICK_CTRL_INTEN_BIT | SYSTICK_CTRL_CLK_SRC_BIT;
}

/*********************************************************************
 * Service Name: SysTick_StartBusyWait
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): a_TimeInMilliSeconds - Time in milliseconds
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initialize the SysTick timer with the specified time in milliseconds
 * using polling or busy-wait technique.
 **********************************************************************/
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds) {

    if( ((16000 * a_TimeInMilliSeconds - 1) > 0x00FFFFFF) || ((16000 * a_TimeInMilliSeconds - 1) < 0x01) ) {
        return; //Error Checking if the number of ticks is more than available in regiester
    }
    SYSTICK_CTRL_REG    = 0;              /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_RELOAD_REG  = (16000 * a_TimeInMilliSeconds) - 1 ;  /* Set the Reload value with a_TimeInMilliSeconds converted to ticks */
    SYSTICK_CURRENT_REG = 0;              /* Clear the Current Register value */
    /* Configure the SysTick Control Register
     * Enable the SysTick Timer (ENABLE = 1)
     * Disable SysTick Interrupt (INTEN = 0)
     * Choose the clock source to be System Clock (CLK_SRC = 1) */
    SYSTICK_CTRL_REG   |= SYSTICK_CTRL_ENABLE_BIT | SYSTICK_CTRL_CLK_SRC_BIT ;

    while(!(SYSTICK_CTRL_REG & (1<<16)));
}

/*********************************************************************
 * Service Name: SysTick_Handler
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Handler for SysTick interrupt to call the call-back function.
 **********************************************************************/
void SysTick_Handler(void) {
    if(g_SysTickCallBackPtr != NULL_PTR)
    {
        /* Call the Function from Scheduler using callback function concept */
        (*g_SysTickCallBackPtr)();
    }
}

/*********************************************************************
 * Service Name: SysTick_SetCallBack
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Ptr2Func - Pointer to the callback function
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set up the SysTick Timer call back to be executed in
 * SysTick Handler.
 **********************************************************************/
void SysTick_SetCallBack(volatile void (*Ptr2Func)(void)) {
    g_SysTickCallBackPtr = Ptr2Func;
}

/*********************************************************************
 * Service Name: SysTick_Stop
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Stop the SysTick timer.
 **********************************************************************/
void SysTick_Stop(void) {
    /* Configure the SysTick Control Register
     * Disable the SysTick Timer (ENABLE = 0) */
    SYSTICK_CTRL_REG &= ~SYSTICK_CTRL_ENABLE_BIT;
}

/*********************************************************************
 * Service Name: SysTick_Start
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Start or Resume the SysTick timer.
 **********************************************************************/
void SysTick_Start(void) {
    /* Configure the SysTick Control Register
     * Enable the SysTick Timer (ENABLE = 1) */
    SYSTICK_CTRL_REG |= SYSTICK_CTRL_ENABLE_BIT;
}


/*********************************************************************
 * Service Name: SysTick_DeInit
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: De-initialize the SysTick Timer.
 **********************************************************************/
void SysTick_DeInit(void) {
    /* Configure the SysTick Control Register
    * Disable the SysTick Timer (ENABLE = 0)
    * Disable SysTick Interrupt (INTEN = 0) */
    SYSTICK_CTRL_REG    = 0;              /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_RELOAD_REG  = 0 ;             /* Clear the Reload Register */
    SYSTICK_CURRENT_REG = 0;              /* Clear the Current Register value */
}
