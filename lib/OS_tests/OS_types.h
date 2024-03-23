#ifndef OS_TYPES_H
#define OS_TYPES_H
#include <stdint.h>

typedef struct {
  const char *name;   ///< name of the mutex
  uint32_t attr_bits; ///< attribute bits
  void *cb_mem;       ///< memory for control block
  uint32_t cb_size;   ///< size of provided memory for control block
} os_mutex_attr_t;

typedef uint8_t os_mutex_id;
typedef os_mutex_attr_t os_mutex_attr;

#endif