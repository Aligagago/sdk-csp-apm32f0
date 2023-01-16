/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-20     Abbcc        first version
 */

#ifndef __DRV_COMMON_H__
#define __DRV_COMMON_H__

#include <rtthread.h>
#include <rthw.h>
#ifdef RT_USING_DEVICE
    #include <rtdevice.h>
#endif

#include <apm32f0xx.h>

#include "apm32f0xx_gpio.h"
#include "apm32f0xx_syscfg.h"
#include "apm32f0xx_rcm.h"
#include "apm32f0xx_misc.h"
#include "apm32f0xx_eint.h"
#include "apm32f0xx_usart.h"

#if defined(RT_USING_ADC)
    #include "apm32f0xx_adc.h"
#endif
#if defined(RT_USING_DAC)
    #include "apm32f0xx_dac.h"
#endif
#if defined(RT_USING_RTC)
    #include "apm32f0xx_rtc.h"
    #include "apm32f0xx_pmu.h"
#endif
#if defined(RT_USING_SPI)
    #include "apm32f0xx_spi.h"
#endif
#if defined(RT_USING_HWTIMER) || defined(RT_USING_PWM)
    #include "apm32f0xx_tmr.h"
#endif
#if defined(RT_USING_WDT)
    #include "apm32f0xx_iwdt.h"
    #include "apm32f0xx_wwdt.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

void _Error_Handler(char *s, int num);

#ifndef Error_Handler
#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#endif

#define DMA_NOT_AVAILABLE ((DMA_INSTANCE_TYPE *)0xFFFFFFFFU)

#define __APM32_PORT(port)  GPIO##port##_BASE
#define GET_PIN(PORTx,PIN) (rt_base_t)((16 * ( ((rt_base_t)__APM32_PORT(PORTx) - (rt_base_t)GPIOA_BASE)/(0x0400UL) )) + PIN)

#define APM32_FLASH_START_ADRESS       ROM_START
#define APM32_FLASH_SIZE               ROM_SIZE
#define APM32_FLASH_END_ADDRESS        ROM_END

#define APM32_SRAM_SIZE               RAM_SIZE
#define APM32_SRAM_START              RAM_START
#define APM32_SRAM_END                RAM_END

#if defined(__ARMCC_VERSION)
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN      ((void *)&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="CSTACK"
#define HEAP_BEGIN      (__segment_end("CSTACK"))
#else
extern int __bss_end;
#define HEAP_BEGIN      ((void *)&__bss_end)
#endif

#define HEAP_END        APM32_SRAM_END


#ifdef __cplusplus
}
#endif

#endif
