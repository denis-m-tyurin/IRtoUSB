/**
  ******************************************************************************
  * @file           : USB_DEVICE  
  * @version        : v1.0_Cube
  * @brief          : This file implements the USB Device 
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  * 1. Redistributions of source code must retain the above copyright notice,
  * this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  * this list of conditions and the following disclaimer in the documentation
  * and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of its contributors
  * may be used to endorse or promote products derived from this software
  * without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/

#include "usb_device.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_hid.h"

/* USB Device Core handle declaration */
USBD_HandleTypeDef hUsbDeviceFS;

/* init function */				        
void MX_USB_DEVICE_Init(void)
{
  /* Init Device Library,Add Supported Class and Start the library*/
  USBD_Init(&hUsbDeviceFS, &FS_Desc, DEVICE_FS);

  USBD_RegisterClass(&hUsbDeviceFS, &USBD_HID);

  USBD_Start(&hUsbDeviceFS);

}

void MX_USB_DEVICE_SendHIDAction(uint8_t action)
{
	uint8_t buf[3];
	
	buf[0] = action;
	buf[1] = 0;
	buf[2] = 0;
	USBD_HID_SendReport(&hUsbDeviceFS, 
                      buf,
                      3);	
}

uint8_t USB_HIDDEVICE_KeyboardStructInit(USB_HIDDEVICE_Keyboard_t* Keyboard_Data) {
	/* Set defaults */
	Keyboard_Data->L_CTRL = USB_HIDDEVICE_Button_Released;
	Keyboard_Data->L_ALT = USB_HIDDEVICE_Button_Released;
	Keyboard_Data->L_SHIFT = USB_HIDDEVICE_Button_Released;
	Keyboard_Data->L_GUI = USB_HIDDEVICE_Button_Released;
	Keyboard_Data->R_CTRL = USB_HIDDEVICE_Button_Released;
	Keyboard_Data->R_ALT = USB_HIDDEVICE_Button_Released;
	Keyboard_Data->R_SHIFT = USB_HIDDEVICE_Button_Released;
	Keyboard_Data->R_GUI = USB_HIDDEVICE_Button_Released;
	Keyboard_Data->Key1 = 0;
	Keyboard_Data->Key2 = 0;
	Keyboard_Data->Key3 = 0;
	Keyboard_Data->Key4 = 0;
	Keyboard_Data->Key5 = 0;
	Keyboard_Data->Key6 = 0;
	
	/* Return currect status */
	return USBD_OK;
}

uint8_t USB_HIDDEVICE_KeyboardSend(USB_HIDDEVICE_Keyboard_t* Keyboard_Data) {
	uint8_t buff[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};; /* 9 bytes long report */
	
	/* Report ID */
	buff[0] = 0x01; /* Keyboard */
	
	/* Control buttons */
	buff[1] = 0;
	buff[1] |= Keyboard_Data->L_CTRL 	<< 0;	/* Bit 0 */
	buff[1] |= Keyboard_Data->L_SHIFT 	<< 1;	/* Bit 1 */
	buff[1] |= Keyboard_Data->L_ALT 	<< 2;	/* Bit 2 */
	buff[1] |= Keyboard_Data->L_GUI 	<< 3;	/* Bit 3 */
	buff[1] |= Keyboard_Data->R_CTRL 	<< 4;	/* Bit 4 */
	buff[1] |= Keyboard_Data->R_SHIFT 	<< 5;	/* Bit 5 */
	buff[1] |= Keyboard_Data->R_ALT 	<< 6;	/* Bit 6 */
	buff[1] |= Keyboard_Data->R_GUI 	<< 7;	/* Bit 7 */
	
	/* Padding */
	buff[2] = 0x00;
	
	/* Keys */
	buff[3] = Keyboard_Data->Key1;
	buff[4] = Keyboard_Data->Key2;
	buff[5] = Keyboard_Data->Key3;
	buff[6] = Keyboard_Data->Key4;
	buff[7] = Keyboard_Data->Key5;
	buff[8] = Keyboard_Data->Key6;
	
	/* Send to USB */
	USBD_HID_SendReport(&hUsbDeviceFS, buff, 9);
	
	/* Return connected */
	return USBD_OK;	
}

uint8_t USB_HIDDEVICE_KeyboardReleaseAll(void) {
	uint8_t buff[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; /* 9 bytes long report */
	
	/* Report ID */
	buff[0] = 0x01; /* Keyboard */
	
	/* Send to USB */
	USBD_HID_SendReport(&hUsbDeviceFS, buff, 9);
	
	/* Return connected */
	return USBD_OK;
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
