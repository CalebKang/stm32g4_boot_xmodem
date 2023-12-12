/*
 * uart.c
 *
 *  Created on: Dec 12, 2023
 *      Author: calebkang
 */
#include "main.h"

/**
 * @brief   Receives data from UART.
 * @param   *data: Array to save the received data.
 * @param   length:  Size of the data.
 * @return  status: Report about the success of the receiving.
 */
uart_status uart_receive(uint8_t *data, uint16_t length)
{
  uart_status status = UART_ERROR;

  if (HAL_OK == HAL_UART_Receive(&huart2, data, length, UART_TIMEOUT))
  {
    status = UART_OK;
  }

  return status;
}

/**
 * @brief   Transmits a string to UART.
 * @param   *data: Array of the data.
 * @return  status: Report about the success of the transmission.
 */
uart_status uart_transmit_str(uint8_t *data)
{
  uart_status status = UART_ERROR;
  uint16_t length = 0u;

  /* Calculate the length. */
  while ('\0' != data[length])
  {
    length++;
  }

  if (HAL_OK == HAL_UART_Transmit(&huart2, data, length, UART_TIMEOUT))
  {
    status = UART_OK;
  }

  return status;
}

/**
 * @brief   Transmits a single char to UART.
 * @param   *data: The char.
 * @return  status: Report about the success of the transmission.
 */
uart_status uart_transmit_ch(uint8_t data)
{
  uart_status status = UART_ERROR;

  /* Make available the UART module. */
  if (HAL_UART_STATE_TIMEOUT == HAL_UART_GetState(&huart2))
  {
    HAL_UART_Abort(&huart2);
  }

  if (HAL_OK == HAL_UART_Transmit(&huart2, &data, 1u, UART_TIMEOUT))
  {
    status = UART_OK;
  }
  return status;
}

