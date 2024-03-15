#include "global.h"
#include "stm32f4xx_hal_uart.h"


const osMutexAttr_t uartMutex_attributes = {
    .name = "uartMutex",
    osMutexPrioInherit,  // attr_bits
    NULL,                // memory for control block   
    0U                   // size for control block
};

void putsMutex(char *text){
    if( uartMutex_M != NULL ){
        osStatus_t aquire_status = osMutexAcquire( uartMutex_M, osWaitForever);
        if( aquire_status != osOK)
            // puts("osMutexAcquire failed :");
            // puts(osStatusToString(aquire_status));
            return;
        puts(text); 
        osStatus_t release_status = osMutexRelease( uartMutex_M );
        if(release_status != osOK){
            // puts("osMutexrelease failed :");
            // puts(osStatusToString(release_status));
            return;
        }
        
    }
}

char *getsMutex(char *text){
    char *original_str = text;
    if( uartMutex_M != NULL ){
        osStatus_t aquire_status = osMutexAcquire( uartMutex_M, osWaitForever);
        if( aquire_status != osOK)
            return NULL;  // Retourne NULL en cas d'échec de l'acquisition du mutex

        // Appeler la fonction gets avec le buffer alloué
        gets(text);  

        osStatus_t release_status = osMutexRelease( uartMutex_M );
        if(release_status != osOK){
            return NULL;  // Retourne NULL en cas d'échec de la libération du mutex
        }
    }
    return original_str;
}

bool uart_data_available() {
    // Check if data is available to read from UART
    return (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE) != RESET);
}

bool send_command(const char *command, char *response_buffer) {
    if( uartMutex_M != NULL ){
        osStatus_t aquire_status = osMutexAcquire( uartMutex_M, osWaitForever);
        if( aquire_status != osOK)
        return false;
        
        if (puts(command) < 0) {
            return false; // Error sending command
        }
        // Receive response
        char *response = gets(response_buffer);
        if (response == NULL) {
            return false; // Error receiving response
        }
        osStatus_t release_status = osMutexRelease( uartMutex_M );
        if(release_status != osOK){
            // puts("osMutexrelease failed :");
            // puts(osStatusToString(release_status));
            return false;
        }
        
    }
    return true; // Command sent successfully and response received
}


char* osStatusToString(osStatus_t status) {
    switch (status) {
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

char* longlong_to_string(long long num) {
    static char buffer[32]; // Declaration of the output buffer

    char* ptr = buffer; // Pointer to the beginning of the buffer

    // Check the sign of the number
    if (num < 0) {
        *(ptr++) = '-';
        num = -num;
    }

    // Convert digits to characters, from right to left
    char temp[32];
    int digits = 0;
    do {
        temp[digits++] = '0' + num % 10;
        num /= 10;
    } while (num != 0);

    // Copy the converted number characters into the output buffer, reversing the order
    while (digits > 0) {
        *(ptr++) = temp[--digits];
    }

    // Add the null character at the end of the string
    *ptr = '\0';

    // Return the output buffer
    return buffer;
}
