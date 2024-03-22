#include "global.h"
#include "stm32f4xx_hal_uart.h"

bool is_comptetion_started = false;

const osMutexAttr_t uartMutex_attributes = {
    .name = "uartMutex",
    osMutexPrioInherit, // attr_bits
    NULL,               // memory for control block
    0U                  // size for control block
};

void putsMutex(char *text)
{
    if (uartMutex_M != NULL)
    {
        osStatus_t aquire_status = osMutexAcquire(uartMutex_M, osWaitForever);
        if (aquire_status != osOK)
            // puts("osMutexAcquire failed :");
            // puts(osStatusToString(aquire_status));
            return;
        puts(text);
        osStatus_t release_status = osMutexRelease(uartMutex_M);
        if (release_status != osOK)
        {
            // puts("osMutexrelease failed :");
            // puts(osStatusToString(release_status));
            return;
        }
    }
}

char *getsMutex(char *text)
{
    char *original_str = text;
    if (uartMutex_M != NULL)
    {
        osStatus_t aquire_status = osMutexAcquire(uartMutex_M, osWaitForever);
        if (aquire_status != osOK)
            return NULL; // Retourne NULL en cas d'échec de l'acquisition du mutex

        // Appeler la fonction gets avec le buffer alloué
        gets(text);

        osStatus_t release_status = osMutexRelease(uartMutex_M);
        if (release_status != osOK)
        {
            return NULL; // Retourne NULL en cas d'échec de la libération du mutex
        }
    }
    return original_str;
}

bool uart_data_available()
{
    // Check if data is available to read from UART
    return (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE));
}

bool send_command(const char *command, char *response_buffer)
{
    if (uartMutex_M != NULL)
    {
        osStatus_t aquire_status = osMutexAcquire(uartMutex_M, osWaitForever);
        if (aquire_status != osOK)
            return false;

        if (puts(command) < 0)
        {
            return false; // Error sending command
        }
        // Receive response
        char *response = gets(response_buffer);
        if (response == NULL)
        {
            return false; // Error receiving response
        }
        osStatus_t release_status = osMutexRelease(uartMutex_M);
        if (release_status != osOK)
        {
            // puts("osMutexrelease failed :");
            // puts(osStatusToString(release_status));
            return false;
        }
    }
    return true; // Command sent successfully and response received
}

char *osStatusToString(osStatus_t status)
{
    switch (status)
    {
    case osOK:
        return "osOK";
    case osError:
        return "osError";
    case osErrorTimeout:
        return "osErrorTimeout";
    case osErrorResource:
        return "osErrorResource";
    case osErrorParameter:
        return "osErrorParameter";
    case osErrorNoMemory:
        return "osErrorNoMemory";
    case osErrorISR:
        return "osErrorISR";
    case osStatusReserved:
        return "osStatusReserved";
    default:
        return "Unknown Status";
    }
}

char *longlong_to_string(long long num)
{
    static char buffer[32]; // Declaration of the output buffer

    char *ptr = buffer; // Pointer to the beginning of the buffer

    // Check the sign of the number
    if (num < 0)
    {
        *(ptr++) = '-';
        num = -num;
    }

    // Convert digits to characters, from right to left
    char temp[32];
    int digits = 0;
    do
    {
        temp[digits++] = '0' + num % 10;
        num /= 10;
    } while (num != 0);

    // Copy the converted number characters into the output buffer, reversing the order
    while (digits > 0)
    {
        *(ptr++) = temp[--digits];
    }

    // Add the null character at the end of the string
    *ptr = '\0';

    // Return the output buffer
    return buffer;
}
void generate_command(T_command_type command_type, int ship_id, int angle,
                      int speed, char *command_buffer)
{
    switch (command_type)
    {
    case MOVE_CMD:
        snprintf(command_buffer, 100, "MOVE %d %d %d\n", ship_id, angle, speed);
        break;
    case FIRE_CMD:
        snprintf(command_buffer, 100, "FIRE %d %d\n", ship_id, angle);
        break;
    case RADAR_CMD:
        snprintf(command_buffer, 100, "RADAR %d\n", ship_id);
        break;
    }
}

void set_ship_type(T_ship *ship)
{
    if (ship->id >= 1 && ship->id <= 5)
    {
        ship->ship_type = ATTACKERS_SHIP;
    }
    else if (ship->id > 5 && ship->id <= 7)
    {
        ship->ship_type = EXPLORER_SHIP;
    }
    else if (ship->id >= 8 && ship->id <= 9)
    {
        ship->ship_type = COLLECTOR_SHIP;
    }
    else
    {
        ship->ship_type = UNKNOWN_SHIP;
    }
}
static int _angle = 90;
static int _speed = 0;

void testShip(uint8_t id)
{
    char command_buffer[100];
    if (is_comptetion_started == true)
    {
        if (_angle >= 359)
        {
            _angle = 0;
        }

        if (_speed >= 999)
        {
            _speed = 0;
        }

        _angle += 10;
        _speed += 10;

        generate_command(MOVE_CMD, id, _angle, _speed, command_buffer);
        // generate_command(FIRE_CMD, 1, _angle, _speed, command_buffer);

        putsMutex(command_buffer);
    }
    else
    {
        /* do nothing */
    }
}

char *boolToCString(bool value)
{
    // Copie la représentation en chaîne de caractères du booléen dans le tableau
    if (value)
    {
        return "true\n";
    }
    else
    {
        return "false\n";
    }
}