/*
 * menu.c
 *
 *  Created on: Dec 12, 2023
 *      Author: calebkang
 */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private variables ---------------------------------------------------------*/


/**
  * @brief  Display the Main Menu on HyperTerminal
  * @param  None
  * @retval None
  */
void Main_Menu(void)
{
  uint8_t key = 0;

  while (1)
  {
    uart_transmit_str((uint8_t*)"\r\n=================== Main Menu =============================\r\n");
    uart_transmit_str((uint8_t*)"  1. Download binary with X-MODEM @0x8004000 \r\n");
    uart_transmit_str((uint8_t*)"  2. Download binary to EEPROM \r\n");
    uart_transmit_str((uint8_t*)"  3. Execute the loaded application \r\n");
    uart_transmit_str((uint8_t*)"===========================================================\r\n");

    /* Clean the input path */
    __HAL_UART_FLUSH_DRREGISTER(&huart2);

    /* Receive key */
    while(uart_receive(&key, 1u) != UART_OK);

    switch (key)
    {
    case '1' :
      /* Download user application in the Flash */
      uart_transmit_str((uint8_t*)"Choose binary and Send......\r\n\n");
      xmodem_receive();
      break;

    case '2' :
      /* Put code to write to EEPROM */
      uart_transmit_str((uint8_t*)"Choose binary and Send......\r\n\n");
      /* Need to complement*/
      break;

    case '3' :
      uart_transmit_str((uint8_t*)"Start program execution......\r\n\n");
      flash_jump_to_app();

    default:
      uart_transmit_str((uint8_t*)"Invalid Number ! ==> The number should be either 1, 2 or 3\r");
      break;
    }
  }
}

/**
  * @}
  */
