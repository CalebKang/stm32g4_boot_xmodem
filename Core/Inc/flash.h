/*
 * flash.h
 *
 *  Created on: Dec 12, 2023
 *      Author: calebkang
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

/* Start and end addresses of the user application. */
#define FLASH_APP_START_ADDRESS ((uint32_t)0x08004000u)
#define FLASH_APP_END_ADDRESS   ((uint32_t)(0x08000000u + (128*1024) - 1)) /* Flash : 128K */

/* Status report for the functions. */
typedef enum {
  FLASH_OK              = 0x00u, /**< The action was successful. */
  FLASH_ERROR_SIZE      = 0x01u, /**< The binary is too big. */
  FLASH_ERROR_WRITE     = 0x02u, /**< Writing failed. */
  FLASH_ERROR_READBACK  = 0x04u, /**< Writing was successful, but the content of the memory is wrong. */
  FLASH_ERROR           = 0xFFu  /**< Generic error. */
} flash_status;

flash_status flash_erase(uint32_t address);
flash_status flash_write(uint32_t address, uint64_t *data, uint32_t length);
void flash_jump_to_app(void);

#endif /* INC_FLASH_H_ */
