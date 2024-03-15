#include <math.h>
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif
#include "main.h"
#include "cmsis_os.h"
#include "semphr.h"

osThreadId_t mainTaskHandle;

osThreadId_t attackerTaskHandles_1;
osThreadId_t attackerTaskHandles_2;
osThreadId_t attackerTaskHandles_3;
osThreadId_t attackerTaskHandles_4;
osThreadId_t attackerTaskHandles_5;

osThreadId_t exploratorTaskHandles_1;
osThreadId_t exploratorTaskHandles_2;

osThreadId_t collectorTaskHandles_1;
osThreadId_t collectorTaskHandles_2;

osMutexId_t putsMutex_M;
// SemaphoreHandle_t putsMutex_M = NULL;



void StartMainTask(void *argument);

void StartAttackerTask_1(void *argument);
void StartAttackerTask_2(void *argument);
void StartAttackerTask_3(void *argument);
void StartAttackerTask_4(void *argument);
void StartAttackerTask_5(void *argument);

void StartExploratorTask_1(void *argument);
void StartExploratorTask_2(void *argument);

void StartCollectorTask_1(void *argument);
void StartCollectorTask_2(void *argument);

void putsMutex(char *text);
char* osStatusToString(osStatus_t status);

    


int main(void)
{
    hardware_init();

    osKernelInitialize();
    

    const osThreadAttr_t mainTask_attributes = {
        .name = "mainTask",
        .priority = (osPriority_t)osPriorityNormal1,
        .stack_size = 2048,
    };
    mainTaskHandle = osThreadNew(StartMainTask, NULL, &mainTask_attributes);

    const osThreadAttr_t attackersTask_attributes = {
        .name = "attackersTask",
        .priority = (osPriority_t)osPriorityNormal,
        .stack_size = 2048,
    };

    attackerTaskHandles_1 = osThreadNew(StartAttackerTask_1, NULL, &attackersTask_attributes);
    attackerTaskHandles_2 = osThreadNew(StartAttackerTask_2, NULL, &attackersTask_attributes);
    attackerTaskHandles_3 = osThreadNew(StartAttackerTask_3, NULL, &attackersTask_attributes);
    attackerTaskHandles_4 = osThreadNew(StartAttackerTask_4, NULL, &attackersTask_attributes);
    attackerTaskHandles_5 = osThreadNew(StartAttackerTask_5, NULL, &attackersTask_attributes);

    const osThreadAttr_t exploratorsTask_attributes = {
        .name = "exploratorsTask",
        .priority = (osPriority_t)osPriorityNormal,
        .stack_size = 2048,
    };
    exploratorTaskHandles_1 = osThreadNew(StartExploratorTask_1, NULL, &exploratorsTask_attributes);
    exploratorTaskHandles_2 = osThreadNew(StartExploratorTask_2, NULL, &exploratorsTask_attributes);    

    const osThreadAttr_t collectorsTask_attributes = {
        .name = "collectorsTask",
        .priority = (osPriority_t)osPriorityNormal,
        .stack_size = 2048,
    };
    collectorTaskHandles_1 = osThreadNew(StartCollectorTask_1, NULL, &collectorsTask_attributes);
    collectorTaskHandles_2 = osThreadNew(StartCollectorTask_2, NULL, &collectorsTask_attributes);
    
    const osMutexAttr_t mutex_attributes = {
        .name = "putsMutex",
        osMutexPrioInherit,  // attr_bits
        NULL,                // memory for control block   
        0U                   // size for control block
    };
    putsMutex_M = osMutexNew(&mutex_attributes);
    puts("BOOTED");

    osKernelStart();

    while (1)
    {
    }
}

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
    static char buffer[32]; // Déclaration du tampon de sortie

    char* ptr = buffer; // Pointeur vers le début du tampon

    // Vérifier le signe du nombre
    if (num < 0) {
        *(ptr++) = '-';
        num = -num;
    }

    // Convertir les chiffres en caractères, de droite à gauche
    char temp[32];
    int digits = 0;
    do {
        temp[digits++] = '0' + num % 10;
        num /= 10;
    } while (num != 0);

    // Copier les caractères du nombre converti dans le tampon de sortie, en inversant l'ordre
    while (digits > 0) {
        *(ptr++) = temp[--digits];
    }

    // Ajouter le caractère nul à la fin de la chaîne
    *ptr = '\0';

    // Retourner le tampon de sortie
    return buffer;
}

void StartMainTask(void *argument)
{   
    long long heartbit =0;
    putsMutex_M = xSemaphoreCreateMutex();
    putsMutex("Main Thread Task started\n");
    while (1)
    {   
        heartbit ++;
        // putsMutex("Main Thread Task :");
        // putsMutex(longlong_to_string(heartbit));
        putsMutex("Main Thread Task :");
        osDelay(100);
    }
}

void StartAttackerTask_1(void *argument)
{   
    putsMutex("Attacker Task 1 started\n");
    while (1)
    {
        putsMutex("Attacker Task 1\n");
        osDelay(100);
    }
}

void StartAttackerTask_2(void *argument)
{

    putsMutex("Attacker Task 2 started\n");
    while (1)
    {
        putsMutex("Attacker Task 2\n");
        osDelay(100);
    }
}

void StartAttackerTask_3(void *argument)
{
    putsMutex("Attacker Task 3 started\n");
    while (1)
    {
        putsMutex("Attacker Task 3\n");
        osDelay(100);
    }
}

void StartAttackerTask_4(void *argument)
{
    putsMutex("Attacker Task 4 started\n");
    while (1)
    {
        putsMutex("Attacker Task 4\n");
        osDelay(100);
    }
}

void StartAttackerTask_5(void *argument)
{
    putsMutex("Attacker Task 5 started\n");
    while (1)
    {
        putsMutex("Attacker Task 5\n");
        osDelay(100);
    }
}

void StartExploratorTask_1(void *argument)
{
    putsMutex("Explorer Task 1 started\n");
    while (1)
    {
        putsMutex("Explorer Task 1\n");
        osDelay(100);
    }
}

void StartExploratorTask_2(void *argument)
{
    putsMutex("Explorer Task 2 started\n");
    while (1)
    {
        putsMutex("Explorer Task 2\n");
        osDelay(100);
    }
}

void StartCollectorTask_1(void *argument)
{
    putsMutex("Explorer Task 1 started\n");
    while (1)
    {
        putsMutex("Explorer Task 1\n");
        osDelay(100);
    }
}

void StartCollectorTask_2(void *argument)
{
    putsMutex("Collector Task 2 started\n");
    while (1)
    {
        putsMutex("Collector Task 2\n");
        osDelay(100);
        osThreadYield();
    }
}