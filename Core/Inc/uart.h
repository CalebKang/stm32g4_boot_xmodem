/*
 * uart.h
 *
 *  Created on: Dec 12, 2023
 *      Author: calebkang
 */

#ifndef INC_UART_H_
#define INC_UART_H_

extern UART_HandleTypeDef huart2;

/* Timeout for HAL. */
#define UART_TIMEOUT ((uint16_t)1000u)

/* Status report for the functions. */
typedef enum {
  UART_OK     = 0x00u, /**< The action was successful. */
  UART_ERROR  = 0xFFu  /**< Generic error. */
} uart_status;

uart_status uart_receive(uint8_t *data, uint16_t length);
uart_status uart_transmit_str(uint8_t *data);
uart_status uart_transmit_ch(uint8_t data);

#endif /* SRC_UART_H_ */
