/**
  ******************************************************************************
  * @file           : USB_DEVICE
  * @version        : v1.0_Cube
  * @brief          : Header for usb_device file.
  ******************************************************************************
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __usb_device_H
#define __usb_device_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
#include "stm32f0xx_hal.h"
#include "usbd_def.h"

extern USBD_HandleTypeDef hUsbDeviceFS;

/* USB_Device init function */	
void MX_USB_DEVICE_Init(void);

void MX_USB_DEVICE_SendHIDAction(uint8_t action);
	 
	 /**
 * @brief  Button status enumeration
 */
typedef enum {
	USB_HIDDEVICE_Button_Released = 0x00, /*!< Button is not pressed */
	USB_HIDDEVICE_Button_Pressed = 0x01   /*!< Button is pressed */
} USB_HIDDEVICE_Button_t;

/**
 * @brief  Keyboard structure
 * @note   Keyboard has special 8 buttons (CTRL, ALT, SHIFT, GUI (or WIN), all are left and right).
 *         It also supports 6 others keys to be pressed at same time, let's say Key1 = 'a', Key2 = 'b', and you will get "ab" result on the screen.
 *         If key is not used, then 0x00 value should be set!
 */
typedef struct {
	USB_HIDDEVICE_Button_t L_CTRL;  /*!< Left CTRL button. This parameter can be a value of @ref TM_USB_HIDDEVICE_Button_t enumeration */
	USB_HIDDEVICE_Button_t L_ALT;   /*!< Left ALT button. This parameter can be a value of @ref TM_USB_HIDDEVICE_Button_t enumeration */
	USB_HIDDEVICE_Button_t L_SHIFT; /*!< Left SHIFT button. This parameter can be a value of @ref TM_USB_HIDDEVICE_Button_t enumeration */
	USB_HIDDEVICE_Button_t L_GUI;   /*!< Left GUI (Win) button. This parameter can be a value of @ref TM_USB_HIDDEVICE_Button_t enumeration */
	USB_HIDDEVICE_Button_t R_CTRL;  /*!< Right CTRL button. This parameter can be a value of @ref TM_USB_HIDDEVICE_Button_t enumeration */
	USB_HIDDEVICE_Button_t R_ALT;   /*!< Right ALT button. This parameter can be a value of @ref TM_USB_HIDDEVICE_Button_t enumeration */
	USB_HIDDEVICE_Button_t R_SHIFT; /*!< Right SHIFT button. This parameter can be a value of @ref TM_USB_HIDDEVICE_Button_t enumeration */
	USB_HIDDEVICE_Button_t R_GUI;   /*!< Right GUI (Win) button. This parameter can be a value of @ref TM_USB_HIDDEVICE_Button_t enumeration */
	uint8_t Key1;                      /*!< Key used with keyboard. This can be whatever. Like numbers, letters, everything. */
	uint8_t Key2;                      /*!< Key used with keyboard. This can be whatever. Like numbers, letters, everything. */
	uint8_t Key3;                      /*!< Key used with keyboard. This can be whatever. Like numbers, letters, everything. */
	uint8_t Key4;                      /*!< Key used with keyboard. This can be whatever. Like numbers, letters, everything. */
	uint8_t Key5;                      /*!< Key used with keyboard. This can be whatever. Like numbers, letters, everything. */
	uint8_t Key6;                      /*!< Key used with keyboard. This can be whatever. Like numbers, letters, everything. */
} USB_HIDDEVICE_Keyboard_t;

/**
 * @brief  Sets default values to work with keyboard
 * @param  *Keyboard_Data: Pointer to empty @ref TM_USB_HIDDEVICE_Keyboard_t structure
 * @retval Member of @ref TM_USB_HIDDEVICE_Status_t enumeration
 */
uint8_t USB_HIDDEVICE_KeyboardStructInit(USB_HIDDEVICE_Keyboard_t* Keyboard_Data);

/**
 * @brief  Sends keyboard report over USB
 * @param  *Keyboard_Data: Pointer to @ref TM_USB_HIDDEVICE_Keyboard_t structure to get data from
 * @retval Member of @ref TM_USB_HIDDEVICE_Status_t enumeration
 */
uint8_t USB_HIDDEVICE_KeyboardSend(USB_HIDDEVICE_Keyboard_t* Keyboard_Data);

/**
 * @brief  Release all buttons from keyboard
 * @note   If you press a button and don't release it, computer will detect like long pressed button
 * @param  None
 * @retval Member of @ref TM_USB_HIDDEVICE_Status_t enumeration
 */
uint8_t USB_HIDDEVICE_KeyboardReleaseAll(void);
	 
#ifdef __cplusplus
}
#endif
#endif /*__usb_device_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
