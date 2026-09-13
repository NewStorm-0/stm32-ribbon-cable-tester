#include "delay.h"
#include "stm32c0xx_hal.h"

void Delay_Us(uint32_t us)
{
    volatile uint32_t count = us * (SystemCoreClock / 3000000U);

    while (count > 0U)
    {
        count--;
        __NOP();
    }
}
