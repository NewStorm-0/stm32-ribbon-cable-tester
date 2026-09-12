#include "hc165.h"
#include "main.h"

#define HC165_CHIP_COUNT  7U
#define HC165_BIT_COUNT   (HC165_CHIP_COUNT * 8U)

/*
 * 读取流程：
 * 1. 拉低 PL#，并行装载各输入状态；
 * 2. 释放 PL#；
 * 3. 连续读取 Q7，并输出 56 个移位时钟；
 * 4. 返回原始 56 位数据。
 */
uint64_t HC165_ReadRaw(void)
{
    uint64_t data = 0;

    HAL_GPIO_WritePin(HC165_CLK_GPIO_Port, HC165_CLK_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(HC165_PL_GPIO_Port, HC165_PL_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(HC165_PL_GPIO_Port, HC165_PL_Pin, GPIO_PIN_SET);

    for (uint32_t i = 0; i < HC165_BIT_COUNT; i++)
    {
        data = data << 1;
        if (HAL_GPIO_ReadPin(HC165_DATA_GPIO_Port, HC165_DATA_Pin) == GPIO_PIN_SET)
        {
            data |= 1;
        }

        HAL_GPIO_WritePin(HC165_CLK_GPIO_Port, HC165_CLK_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(HC165_CLK_GPIO_Port, HC165_CLK_Pin, GPIO_PIN_SET);
    }

    return data;
}
