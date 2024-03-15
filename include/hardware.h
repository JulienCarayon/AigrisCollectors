#ifndef HARDWARE_H
#define HARDWARE_H

#include "main.h"
UART_HandleTypeDef huart2;
void hardware_init(void);
void srand(unsigned int seed);
int rand(void);
int puts(const char *text);
char *gets(char *str);
char *itoa(int value, char *str, int base);
#endif /* HARDWARE_H */
