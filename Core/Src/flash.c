/*
 * flash.c
 *
 *  Created on: Dec 12, 2023
 *      Author: calebkang
 */
#include "main.h"

/* Function pointer for jumping to user application. */
typedef void (*fnc_ptr)(void);

/**
  * @brief  Gets the page of a given address
  * @param  Addr: Address of the FLASH Memory
  * @retval The page of a given address
  */
static uint32_t GetPage(uint32_t Addr)
{
  return (Addr - FLASH_BASE) / FLASH_PAGE_SIZE;;
}
/**
 * @brief   This function erases the memory.
 * @param   address: First address to be erased (the last is the end of the flash).
 * @return  status: Report about the success of the erasing.
 */
flash_status flash_erase(uint32_t address)
{
  flash_status status = FLASH_ERROR;
  FLASH_EraseInitTypeDef EraseInitStruct;
  uint32_t FirstPage = 0, NbOfPages = 0;
  uint32_t PageError = 0;

  HAL_FLASH_Unlock();

  /* Clear OPTVERR bit set on virgin samples */
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);

  /* Erase the user Flash area
   (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

  /* Get the 1st page to erase */
  FirstPage = GetPage(address);

  /* Get the number of pages to erase from 1st page */
  NbOfPages = GetPage(FLASH_APP_END_ADDRESS) - FirstPage + 1;

  /* Fill EraseInit structure*/
  EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
  EraseInitStruct.Page        = FirstPage;
  EraseInitStruct.NbPages     = NbOfPages;

  /* Note: If an erase operation in Flash memory also concerns data in the data or instruction cache,
    you have to make sure that these data are rewritten before they are accessed during code
    execution. If this cannot be done safely, it is recommended to flush the caches by setting the
    DCRST and ICRST bits in the FLASH_CR register. */
  if (HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) != HAL_OK)
  {
    status = FLASH_ERROR;
  }
  else
  {
    status = FLASH_OK;
  }

  HAL_FLASH_Lock();
  return status;
}

/**
 * @brief   This function flashes the memory.
 * @param   address: First address to be written to.
 * @param   *data:   Array of the data that we want to write.
 * @param   *length: Size of the array.
 * @return  status: Report about the success of the writing.
 */
flash_status flash_write(uint32_t address, uint64_t *data, uint32_t length)
{
  flash_status status = FLASH_OK;

  HAL_FLASH_Unlock();

  for(uint32_t i = 0u; (i < length) && (FLASH_OK == status); i++)
  {
    if (FLASH_APP_END_ADDRESS <= address)
    {
      status |= FLASH_ERROR_SIZE;
    }
    else
    {
      /* The actual flashing. If there is an error, then report it. */
      if (HAL_OK != HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address, data[i]))
      {
        status |= FLASH_ERROR_WRITE;
      }
      /* Read back the content of the memory. If it is wrong, then report an error. */
      if (((data[i])) != (*(volatile uint64_t*)address))
      {
        status |= FLASH_ERROR_READBACK;
      }

      /* Shift the address by a word. */
      address += 8u;
    }
  }
  HAL_FLASH_Lock();

  return status;
}

/**
 * @brief   Actually jumps to the user application.
 * @param   void
 * @return  void
 */
void flash_jump_to_app(void)
{
  /* Function pointer to the address of the user application. */
  fnc_ptr jump_to_app;

  System_DeInit();

  jump_to_app = (fnc_ptr)(*(volatile uint32_t*) (FLASH_APP_START_ADDRESS+4u));
  HAL_DeInit();
  /* Change the main stack pointer. */
  __set_MSP(*(volatile uint32_t*)FLASH_APP_START_ADDRESS);
  jump_to_app();
}


