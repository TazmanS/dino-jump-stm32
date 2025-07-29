
#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <stdint.h>

#define INCLUDE_vTaskDelay 1

#define configUSE_PREEMPTION 1
#define configUSE_IDLE_HOOK 0
#define configUSE_TICK_HOOK 0
#define configCPU_CLOCK_HZ ((unsigned long)72000000)
#define configTICK_RATE_HZ ((TickType_t)1000)
#define configMAX_PRIORITIES (5)
#define configMINIMAL_STACK_SIZE ((unsigned short)128)
#define configTOTAL_HEAP_SIZE ((size_t)(10 * 1024))
#define configMAX_TASK_NAME_LEN (16)
#define configUSE_TRACE_FACILITY 0
#define configUSE_16_BIT_TICKS 0
#define configIDLE_SHOULD_YIELD 1
#define configUSE_MUTEXES 1
#define configSUPPORT_DYNAMIC_ALLOCATION 1
#define configSUPPORT_STATIC_ALLOCATION 0
#define configUSE_TIME_SLICING 1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 1
#define configUSE_COUNTING_SEMAPHORES 0
#define configUSE_RECURSIVE_MUTEXES 0

#define configKERNEL_INTERRUPT_PRIORITY 255
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 191

#define xPortPendSVHandler PendSV_Handler
#define vPortSVCHandler SVC_Handler
#define xPortSysTickHandler SysTick_Handler

#ifndef PRIVILEGED_FUNCTION
#define PRIVILEGED_FUNCTION
#endif

#endif /* FREERTOS_CONFIG_H */