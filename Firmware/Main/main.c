#include "led.h"
#include "usb.h"
#include "stm32f0xx.h"
#include "usbd_hid_core.h"
#include "usbd_usr.h"

USB_CORE_HANDLE  USB_Device_dev ;

void Soft_Delay(volatile uint32_t number)
{
        while(number--);
}

 
int main(void)
{
	// Init RGB Led GPIOs
	leds_init();
	
  /* The Application layer has only to call USBD_Init to 
  initialize the USB low level driver, the USB device library, the USB clock 
  ,pins and interrupt service routine (BSP) to start the Library*/
  
  USBD_Init(&USB_Device_dev,
            &USR_desc, 
            &USBD_HID_cb, 
            &USR_cb);

while(1)
	{
		leds_red_on();
		Soft_Delay(10000);
		leds_red_off();
		Soft_Delay(100000);
	}
 
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
 
  /* Infinite loop */
  while (1)
  {
  }
}
#endif
