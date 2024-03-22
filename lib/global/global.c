#include "stm32f4xx_hal_uart.h"
#include <global.h>

char *bool_to_string(bool value) {
  if (value) {
    return "true\n";
  } else {
    return "false\n";
  }
}
