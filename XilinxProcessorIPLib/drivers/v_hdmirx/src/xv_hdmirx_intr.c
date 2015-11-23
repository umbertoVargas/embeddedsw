/******************************************************************************
*
* Copyright (C) 2015 Xilinx, Inc. All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/
/*****************************************************************************/
/**
*
* @file xv_hdmirx_intr.c
*
* This file contains interrupt related functions for Xilinx HDMI RX core.
* Please see xv_hdmirx.h for more details of the driver.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who    Date     Changes
* ----- ------ -------- --------------------------------------------------
* 1.00         10/07/15 Initial release.

* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "xv_hdmirx.h"

/************************** Constant Definitions *****************************/


/***************** Macros (Inline Functions) Definitions *********************/


/**************************** Type Definitions *******************************/


/************************** Function Prototypes ******************************/

static void HdmiRx_PioIntrHandler(XV_HdmiRx *InstancePtr);
static void HdmiRx_TmrIntrHandler(XV_HdmiRx *InstancePtr);
static void HdmiRx_VtdIntrHandler(XV_HdmiRx *InstancePtr);
static void HdmiRx_DdcIntrHandler(XV_HdmiRx *InstancePtr);
static void HdmiRx_AuxIntrHandler(XV_HdmiRx *InstancePtr);
static void HdmiRx_AudIntrHandler(XV_HdmiRx *InstancePtr);
static void HdmiRx_LinkStatusIntrHandler(XV_HdmiRx *InstancePtr);

/************************** Variable Definitions *****************************/


/************************** Function Definitions *****************************/

/*****************************************************************************/
/**
*
* This function is the interrupt handler for the HDMI RX driver.
*
* This handler reads the pending interrupt from PIO, DDC, TIMDET, AUX, AUD
* and LNKSTA peripherals, determines the source of the interrupts, clears the
* interrupts and calls callbacks accordingly.
*
* The application is responsible for connecting this function to the interrupt
* system. Application beyond this driver is also responsible for providing
* callbacks to handle interrupts and installing the callbacks using
* XV_HdmiRx_SetCallback() during initialization phase. An example delivered
* with this driver demonstrates how this could be done.
*
* @param	InstancePtr is a pointer to the XV_HdmiRx instance that just
*		interrupted.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void XV_HdmiRx_IntrHandler(void *InstancePtr)
{
	u32 Data;
	XV_HdmiRx *HdmiRxPtr = (XV_HdmiRx *)InstancePtr;

	/* Verify arguments */
	Xil_AssertVoid(HdmiRxPtr != NULL);
	Xil_AssertVoid(HdmiRxPtr->IsReady == XIL_COMPONENT_IS_READY);

	/* PIO */
	Data = XV_HdmiRx_ReadReg(HdmiRxPtr->Config.BaseAddress, (XV_HDMIRX_PIO_STA_OFFSET)) & (XV_HDMIRX_PIO_STA_IRQ_MASK);

	/* Check for IRQ flag set */
	if (Data) {
		/* Jump to PIO handler */
		HdmiRx_PioIntrHandler(HdmiRxPtr);
	}

	/* Timer */
	Data = XV_HdmiRx_ReadReg(HdmiRxPtr->Config.BaseAddress, (XV_HDMIRX_TMR_STA_OFFSET)) & (XV_HDMIRX_TMR_STA_IRQ_MASK);

	/* Check for IRQ flag set */
	if (Data) {
		/* Jump to PIO handler */
		HdmiRx_TmrIntrHandler(HdmiRxPtr);
	}

	/* Video Timing detector */
	Data = XV_HdmiRx_ReadReg(HdmiRxPtr->Config.BaseAddress, (XV_HDMIRX_VTD_STA_OFFSET)) & (XV_HDMIRX_VTD_STA_IRQ_MASK);

	/* Check for IRQ flag set */
	if (Data) {
		/* Jump to video timing detector handler */
		HdmiRx_VtdIntrHandler(HdmiRxPtr);
	}

	/* DDC */
	Data = XV_HdmiRx_ReadReg(HdmiRxPtr->Config.BaseAddress, (XV_HDMIRX_DDC_STA_OFFSET)) & (XV_HDMIRX_DDC_STA_IRQ_MASK);

	/* Is the IRQ flag set */
	if (Data) {
		/* Jump to DDC handler */
		HdmiRx_DdcIntrHandler(HdmiRxPtr);
	}

	/* AUX */
	Data = XV_HdmiRx_ReadReg(HdmiRxPtr->Config.BaseAddress, (XV_HDMIRX_AUX_STA_OFFSET)) & (XV_HDMIRX_AUX_STA_IRQ_MASK);

	/* Check for IRQ flag set */
	if (Data) {
		/* Jump to AUX handler */
		HdmiRx_AuxIntrHandler(HdmiRxPtr);
	}

	/* Audio */
	Data = XV_HdmiRx_ReadReg(HdmiRxPtr->Config.BaseAddress, (XV_HDMIRX_AUD_STA_OFFSET)) & (XV_HDMIRX_AUD_STA_IRQ_MASK);

	/* Check for IRQ flag set */
	if (Data) {
		/* Jump to Audio handler */
		HdmiRx_AudIntrHandler(HdmiRxPtr);
	}

	/* Link status */
	Data = XV_HdmiRx_ReadReg(HdmiRxPtr->Config.BaseAddress, (XV_HDMIRX_LNKSTA_STA_OFFSET)) & (XV_HDMIRX_LNKSTA_STA_IRQ_MASK);

	/* Check for IRQ flag set */
	if (Data) {
		/* Jump to Link Status handler */
		HdmiRx_LinkStatusIntrHandler(HdmiRxPtr);
	}
}

/*****************************************************************************/
/**
*
* This function installs an asynchronous callback function for the given
* HandlerType:
*
* <pre>
* HandlerType                 Callback Function Type
* -------------------------   -----------------------------------------------
* (XV_HDMIRX_HANDLER_VTD)   	  VtdCallback
* (XV_HDMIRX_HANDLER_AUX)      AuxCallback
* (XV_HDMIRX_HANDLER_AUD)      AudCallback
* (XV_HDMIRX_HANDLER_LNKSTA)   LnkStaCallback
* (XV_HDMIRX_HANDLER_PIO)      PioCallback
* </pre>
*
* @param	InstancePtr is a pointer to the HDMI RX core instance.
* @param	HandlerType specifies the type of handler.
* @param	CallbackFunc is the address of the callback function.
* @param	CallbackRef is a user data item that will be passed to the
*		callback function when it is invoked.
*
* @return
*		- XST_SUCCESS if callback function installed successfully.
*		- XST_INVALID_PARAM when HandlerType is invalid.
*
* @note		Invoking this function for a handler that already has been
*		installed replaces it with the new handler.
*
******************************************************************************/
int XV_HdmiRx_SetCallback(XV_HdmiRx *InstancePtr, u32 HandlerType, void *CallbackFunc, void *CallbackRef)
{
	u32 Status;

	/* Verify arguments. */
	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(HandlerType >= (XV_HDMIRX_HANDLER_CONNECT));
	Xil_AssertNonvoid(CallbackFunc != NULL);
	Xil_AssertNonvoid(CallbackRef != NULL);

	/* Check for handler type */
	switch (HandlerType) {

		case (XV_HDMIRX_HANDLER_CONNECT):
			InstancePtr->ConnectCallback = (XV_HdmiRx_Callback)CallbackFunc;
			InstancePtr->ConnectRef = CallbackRef;
			InstancePtr->IsConnectCallbackSet = (TRUE);
			Status = (XST_SUCCESS);
			break;

		case (XV_HDMIRX_HANDLER_AUX):
			InstancePtr->AuxCallback = (XV_HdmiRx_Callback)CallbackFunc;
			InstancePtr->AuxRef = CallbackRef;
			InstancePtr->IsAuxCallbackSet = (TRUE);
			Status = (XST_SUCCESS);
			break;

		case (XV_HDMIRX_HANDLER_AUD):
			InstancePtr->AudCallback = (XV_HdmiRx_Callback)CallbackFunc;
			InstancePtr->AudRef = CallbackRef;
			InstancePtr->IsAudCallbackSet = (TRUE);
			Status = (XST_SUCCESS);
			break;

		case (XV_HDMIRX_HANDLER_LNKSTA):
			InstancePtr->LnkStaCallback = (XV_HdmiRx_Callback)CallbackFunc;
			InstancePtr->LnkStaRef = CallbackRef;
			InstancePtr->IsLnkStaCallbackSet = (TRUE);
			Status = (XST_SUCCESS);
			break;

		// Ddc
		case (XV_HDMIRX_HANDLER_DDC):
			InstancePtr->DdcCallback = (XV_HdmiRx_Callback)CallbackFunc;
			InstancePtr->DdcRef = CallbackRef;
			InstancePtr->IsDdcCallbackSet = (TRUE);
			Status = (XST_SUCCESS);
			break;

		// Stream down
		case (XV_HDMIRX_HANDLER_STREAM_DOWN):
			InstancePtr->StreamDownCallback = (XV_HdmiRx_Callback)CallbackFunc;
			InstancePtr->StreamDownRef = CallbackRef;
			InstancePtr->IsStreamDownCallbackSet = (TRUE);
			Status = (XST_SUCCESS);
			break;

		// Stream Init
		case (XV_HDMIRX_HANDLER_STREAM_INIT):
			InstancePtr->StreamInitCallback = (XV_HdmiRx_Callback)CallbackFunc;
			InstancePtr->StreamInitRef = CallbackRef;
			InstancePtr->IsStreamInitCallbackSet = (TRUE);
			Status = (XST_SUCCESS);
			break;

		// Stream up
		case (XV_HDMIRX_HANDLER_STREAM_UP):
			InstancePtr->StreamUpCallback = (XV_HdmiRx_Callback)CallbackFunc;
			InstancePtr->StreamUpRef = CallbackRef;
			InstancePtr->IsStreamUpCallbackSet = (TRUE);
			Status = (XST_SUCCESS);
			break;

		// HDCP
		case (XV_HDMIRX_HANDLER_HDCP):
			InstancePtr->HdcpCallback = (XV_HdmiRx_Callback)CallbackFunc;
			InstancePtr->HdcpRef = CallbackRef;
			InstancePtr->IsHdcpCallbackSet = (TRUE);
			Status = (XST_SUCCESS);
			break;

		default:
			Status = (XST_INVALID_PARAM);
			break;
	}

	return Status;
}

/*****************************************************************************/
/**
*
* This function is the interrupt handler for the HDMI RX Timing Detector
* (TIMDET) peripheral.
*
* @param	InstancePtr is a pointer to the XV_HdmiRx core instance.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
static void HdmiRx_VtdIntrHandler(XV_HdmiRx *InstancePtr)
{
	u32 Data;
	u32 Status;

	/* Read Video timing detector Status register */
	Status = XV_HdmiRx_ReadReg(InstancePtr->Config.BaseAddress, (XV_HDMIRX_VTD_STA_OFFSET));

	/* Check for timing parameters ready event */
	if ((Status) & (XV_HDMIRX_VTD_STA_TPR_EVT_MASK)) {

		// Clear event flag
		XV_HdmiRx_WriteReg(InstancePtr->Config.BaseAddress, (XV_HDMIRX_VTD_STA_OFFSET), (XV_HDMIRX_VTD_STA_TPR_EVT_MASK));

		// Read video timing
		XV_HdmiRx_GetVideoTiming(InstancePtr);

	    // Set stream status to up
		InstancePtr->Stream.State = XV_HDMIRX_STATE_STREAM_UP;			// The stream is up

		// Call stream up callback
		if (InstancePtr->IsStreamUpCallbackSet) {
			InstancePtr->StreamUpCallback(InstancePtr->StreamUpRef);
		}
	}
}

/*****************************************************************************/
/**
*
* This function is the interrupt handler for the HDMI RX DDC peripheral.
*
* @param	InstancePtr is a pointer to the XV_HdmiRx core instance.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
static void HdmiRx_DdcIntrHandler(XV_HdmiRx *InstancePtr)
{
	u32 Status;

	/* Read Status register */
	Status = XV_HdmiRx_ReadReg(InstancePtr->Config.BaseAddress, (XV_HDMIRX_DDC_STA_OFFSET));

	/* Check for HDCP write event */
	if ((Status) & (XV_HDMIRX_DDC_STA_HDCP_WR_EVT_MASK)) {

		// Clear event flag
		XV_HdmiRx_WriteReg(InstancePtr->Config.BaseAddress, (XV_HDMIRX_DDC_STA_OFFSET), (XV_HDMIRX_DDC_STA_HDCP_WR_EVT_MASK));

		/* Callback */
		if (InstancePtr->IsHdcpCallbackSet) {
			InstancePtr->HdcpCallback(InstancePtr->HdcpRef);
		}
	}

	/* Check for HDCP read event */
	if ((Status) & (XV_HDMIRX_DDC_STA_HDCP_RD_EVT_MASK)) {

		// Clear event flag
		XV_HdmiRx_WriteReg(InstancePtr->Config.BaseAddress, (XV_HDMIRX_DDC_STA_OFFSET), (XV_HDMIRX_DDC_STA_HDCP_RD_EVT_MASK));

		/* Callback */
		if (InstancePtr->IsHdcpCallbackSet) {
			InstancePtr->HdcpCallback(InstancePtr->HdcpRef);
		}
	}
}

/*****************************************************************************/
/**
*
* This function is the interrupt handler for the HDMI RX PIO peripheral.
*
* @param	InstancePtr is a pointer to the XV_HdmiRx core instance.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
static void HdmiRx_PioIntrHandler(XV_HdmiRx *InstancePtr)
{
	u32 Event;
	u32 Data;

	/* Read PIO IN Event register.*/
	Event = XV_HdmiRx_ReadReg(InstancePtr->Config.BaseAddress, (XV_HDMIRX_PIO_IN_EVT_OFFSET));

	/* Clear event flags */
	XV_HdmiRx_WriteReg(InstancePtr->Config.BaseAddress, (XV_HDMIRX_PIO_IN_EVT_OFFSET), (Event));

	/* Read data */
	Data = XV_HdmiRx_ReadReg(InstancePtr->Config.BaseAddress, (XV_HDMIRX_PIO_IN_OFFSET));

	// Cable detect event has occurred
	if ((Event) & (XV_HDMIRX_PIO_IN_DET_MASK)) {

		// Cable is connected
		if ((Data) & (XV_HDMIRX_PIO_IN_DET_MASK)) {
			// Set connected flag
			InstancePtr->Stream.IsConnected = (TRUE);
		}

		// Cable is disconnected
		else {
			// Clear connected flag
			InstancePtr->Stream.IsConnected = (FALSE);

			// Clear SCDC variables
			XV_HdmiRx_DdcScdcClear(InstancePtr);
		}

		// Check if user callback has been registered
		if (InstancePtr->IsConnectCallbackSet) {
			InstancePtr->ConnectCallback(InstancePtr->ConnectRef);
		}
	}

	// Link ready event has occurred
	if ((Event) & (XV_HDMIRX_PIO_IN_LNK_RDY_MASK)) {

	// Set stream status to idle
		InstancePtr->Stream.State = XV_HDMIRX_STATE_STREAM_IDLE;			// The stream idle

		// Load timer
		XV_HdmiRx_TmrStart(InstancePtr, 1000000);			// 10 ms @ 100 MHz
	}

	// Video ready event has occurred
	if ((Event) & (XV_HDMIRX_PIO_IN_VID_RDY_MASK)) {

		// Stream up
		if ((Data) & (XV_HDMIRX_PIO_IN_VID_RDY_MASK)) {

			// Check the previous state
			// The link can only change to up when the previous state was init
			// Else there was a glitch on the video ready input
			if (InstancePtr->Stream.State == XV_HDMIRX_STATE_STREAM_INIT) {

				// Enable video
				XV_HdmiRx_VideoEnable(InstancePtr, (TRUE));

			// Set stream status to ready
				InstancePtr->Stream.State = XV_HDMIRX_STATE_STREAM_RDY;			// The stream is ready

				// Call stream up callback
				//if (InstancePtr->IsStreamUpCallbackSet) {
				//	InstancePtr->StreamUpCallback(InstancePtr->StreamUpRef);
				//}
			}
		}

		// Stream down
		else {
			/* Assert reset */
			XV_HdmiRx_Reset(InstancePtr, (TRUE));

			/* Clear variables */
			XV_HdmiRx_Clear(InstancePtr);

			// Disable aux and audio peripheral
			// At this state the link clock is not stable.
			// Therefore these two peripheral are disabled to prevent any glitches.
			XV_HdmiRx_AuxDisable(InstancePtr);
			XV_HdmiRx_AudioDisable(InstancePtr);

			// Disable link
			XV_HdmiRx_LinkEnable(InstancePtr, (FALSE));

			// Disable video
			XV_HdmiRx_VideoEnable(InstancePtr, (FALSE));

		// Set stream status to down
			InstancePtr->Stream.State = XV_HDMIRX_STATE_STREAM_DOWN;			// The stream is down

			// Call stream down callback
			if (InstancePtr->IsStreamDownCallbackSet) {
				InstancePtr->StreamDownCallback(InstancePtr->StreamDownRef);
			}
		}
	}

	// SCDC Scrambler Enable
	if ((Event) & (XV_HDMIRX_PIO_IN_SCDC_SCRAMBLER_ENABLE_MASK)) {

		// Enable scrambler
		if ((Data) & (XV_HDMIRX_PIO_IN_SCDC_SCRAMBLER_ENABLE_MASK)) {
			XV_HdmiRx_SetScrambler(InstancePtr, (TRUE));
		}

		// Disable scrambler
		else {
			XV_HdmiRx_SetScrambler(InstancePtr, (FALSE));
		}
	}
}

/*****************************************************************************/
/**
*
* This function is the interrupt handler for the HDMI RX TMR peripheral.
*
* @param	InstancePtr is a pointer to the XV_HdmiRx core instance.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
static void HdmiRx_TmrIntrHandler(XV_HdmiRx *InstancePtr)
{
	u32 Status;

	/* Read Status register */
	Status = XV_HdmiRx_ReadReg(InstancePtr->Config.BaseAddress, (XV_HDMIRX_TMR_STA_OFFSET));

	/* Check for counter event */
	if ((Status) & (XV_HDMIRX_TMR_STA_CNT_EVT_MASK)) {

		// Clear counter event
		XV_HdmiRx_WriteReg(InstancePtr->Config.BaseAddress, (XV_HDMIRX_TMR_STA_OFFSET), (XV_HDMIRX_TMR_STA_CNT_EVT_MASK));

		// Idle state
		if (InstancePtr->Stream.State == XV_HDMIRX_STATE_STREAM_IDLE) {

			// The link is stable now
			// Then the aux and audio peripherals can be enabled
			XV_HdmiRx_AuxEnable(InstancePtr);
			XV_HdmiRx_AudioEnable(InstancePtr);

			// Release HDMI RX reset
			XV_HdmiRx_Reset(InstancePtr, FALSE);

			// Enable link
			XV_HdmiRx_LinkEnable(InstancePtr, (TRUE));

		    // Set stream status to init
			InstancePtr->Stream.State = XV_HDMIRX_STATE_STREAM_INIT;	// The stream init

			// Load timer
			XV_HdmiRx_TmrStart(InstancePtr, 20000000);			// 200 ms @ 100 MHz
		}

		// Init state
		else if (InstancePtr->Stream.State == XV_HDMIRX_STATE_STREAM_INIT) {

			// Read video properties
			//XV_HdmiRx_GetVideoTiming(InstancePtr);
			XV_HdmiRx_GetVideoProperties(InstancePtr);

			// Call stream init callback
			if (InstancePtr->IsStreamInitCallbackSet) {
				InstancePtr->StreamInitCallback(InstancePtr->StreamInitRef);
			}
		}
	}
}

/*****************************************************************************/
/**
*
* This function is the interrupt handler for the HDMI RX AUX peripheral.
*
* @param	InstancePtr is a pointer to the XV_HdmiRx core instance.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
static void HdmiRx_AuxIntrHandler(XV_HdmiRx *InstancePtr)
{
	u32 Status;
	u8 Index;

	/* Read Status register */
	Status = XV_HdmiRx_ReadReg(InstancePtr->Config.BaseAddress, (XV_HDMIRX_AUX_STA_OFFSET));

	/* Check for new packet */
	if ((Status) & (XV_HDMIRX_AUX_STA_NEW_MASK)) {
		// Clear event flag
		XV_HdmiRx_WriteReg(InstancePtr->Config.BaseAddress, (XV_HDMIRX_AUX_STA_OFFSET), (XV_HDMIRX_AUX_STA_NEW_MASK));

		/* Set HDMI flag */
		InstancePtr->Stream.IsHdmi = (TRUE);

		/* Read header word and update AUX header field */
		InstancePtr->Aux.Header.Data = XV_HdmiRx_ReadReg(InstancePtr->Config.BaseAddress, (XV_HDMIRX_AUX_DAT_OFFSET));

		for (Index = 0x0; Index < 8; Index++) {
			/* Read data word and update AUX data field */
			InstancePtr->Aux.Data.Data[Index] = XV_HdmiRx_ReadReg(InstancePtr->Config.BaseAddress, (XV_HDMIRX_AUX_DAT_OFFSET));
		}

		/* Callback */
		if (InstancePtr->IsAuxCallbackSet) {
			InstancePtr->AuxCallback(InstancePtr->AuxRef);
		}
	}
}

/*****************************************************************************/
/**
*
* This function is the interrupt handler for the HDMI RX AUD peripheral.
*
* @param	InstancePtr is a pointer to the XV_HdmiRx core instance.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
static void HdmiRx_AudIntrHandler(XV_HdmiRx *InstancePtr)
{
	u32 Status;

	// Read Status register
	Status = XV_HdmiRx_ReadReg(InstancePtr->Config.BaseAddress, (XV_HDMIRX_AUD_STA_OFFSET));

	// Check for active stream event
	if ((Status) & (XV_HDMIRX_AUD_STA_ACT_EVT_MASK)) {

		// Clear event flag
		XV_HdmiRx_WriteReg(InstancePtr->Config.BaseAddress, (XV_HDMIRX_AUD_STA_OFFSET), (XV_HDMIRX_AUD_STA_ACT_EVT_MASK));

		InstancePtr->Stream.Audio.Active = (TRUE);
	}

	// Check for audio channel event
	if ((Status) & (XV_HDMIRX_AUD_STA_CH_EVT_MASK)) {

		// Clear event flag
		XV_HdmiRx_WriteReg(InstancePtr->Config.BaseAddress, (XV_HDMIRX_AUD_STA_OFFSET), (XV_HDMIRX_AUD_STA_CH_EVT_MASK));

		// Active channels
		switch ((Status >> XV_HDMIRX_AUD_STA_AUD_CH_SHIFT) & XV_HDMIRX_AUD_STA_AUD_CH_MASK) {

			// 8 channels
			case 3 :
				InstancePtr->Stream.Audio.Channels = 8;
				break;

			// 6 channels
			case 2 :
				InstancePtr->Stream.Audio.Channels = 6;
				break;

			// 4 channels
			case 1 :
				InstancePtr->Stream.Audio.Channels = 4;
				break;

			// 2 channels
			default :
				InstancePtr->Stream.Audio.Channels = 2;
				break;
		}

		/* Callback */
		if (InstancePtr->IsAudCallbackSet) {
			InstancePtr->AudCallback(InstancePtr->AudRef);
		}
	}
}

/*****************************************************************************/
/**
*
* This function is the interrupt handler for the HDMI RX Link Status
* (LNKSTA) peripheral.
*
* @param	InstancePtr is a pointer to the XV_HdmiRx core instance.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
static void HdmiRx_LinkStatusIntrHandler(XV_HdmiRx *InstancePtr)
{
	/* Callback */
	if (InstancePtr->IsLnkStaCallbackSet) {
		InstancePtr->LnkStaCallback(InstancePtr->LnkStaRef);
	}
}
