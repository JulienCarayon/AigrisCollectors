#ifndef OS_TYPES_H
#define OS_TYPES_H

#include "cmsis_os.h"

typedef osMutexId_t os_mutex_id;
typedef osMutexAttr_t os_mutex_attr;

#define os_wait_forever osWaitForever

typedef osThreadId_t os_thread_id;

typedef struct {
  uint16_t uint16_data_1;
  uint16_t uint16_data_2;
  uint16_t uint16_data_3;
  uint8_t uint8_data_1;
  uint8_t uint8_data_2;
} os_T_Memory_block;

#endif