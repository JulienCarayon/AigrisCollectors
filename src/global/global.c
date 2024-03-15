#include "global.h"

void putsMutex(char *text){
    if( putsMutex_M != NULL ){
        osStatus_t aquire_status = osMutexAcquire( putsMutex_M, osWaitForever);
        if( aquire_status == osOK){
            puts(text); // Appelez puts après avoir libéré le mutex
            // puts("\n");
           osStatus_t release_status = osMutexRelease( putsMutex_M );
           if(release_status != osOK){
            puts("osMutexrelease failed :");
            puts(osStatusToString(release_status));
           }
        }
        else{
            puts("osMutexAcquire failed :");
            puts(osStatusToString(aquire_status));
        }
    }
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
