/******************************************************************************
 *
 * Module: SysTick
 *
 * File Name: SysTick.h
 *
 * Description: Header file for the ARM Cortex M4 SysTick driver
 *
 * Author: Mohamed Hisham
 *
 *******************************************************************************/

#ifndef SYSTICK_H_
#define SYSTICK_H_


/*******************************************************************************
 * INCLUSIONS                                                                 *
 *******************************************************************************/

#include "std_types.h"

/*******************************************************************************
 * PREPROCESSOR MACROS                                                         *
 *******************************************************************************/

#define SYSTICK_CTRL_ENABLE_BIT         (1<<0)
#define SYSTICK_CTRL_INTEN_BIT          (1<<1)
#define SYSTICK_CTRL_CLK_SRC_BIT        (1<<2)

/*******************************************************************************
 * FUNCTION PROTOTYPES                                                         *
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
void SysTick_Init(uint16 a_TimeInMilliSeconds);

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
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds);

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
void SysTick_Handler(void);


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
void SysTick_SetCallBack(volatile void (*Ptr2Func)(void));

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
void SysTick_Stop(void);

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
void SysTick_Start(void);


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
void SysTick_DeInit(void);

#endif /* SYSTICK_H_ */
