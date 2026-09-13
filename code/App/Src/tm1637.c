#include "tm1637.h"
#include "delay.h"
#include "main.h"

static inline void Set_AutoIncrease_DataCommand(void);
static inline void Set_AddressCommand(uint8_t address);
static inline void Set_DisplayData(uint8_t left, uint8_t right);
static inline void Set_DisplayControl(uint8_t brightness, uint8_t on);

/**
 * @brief Set the character to be displayed on the TM1637 display
 * @param left The character to be displayed on the left grid. This parameter can be a value of @ref Segment codes
 * @param right The character to be displayed on the right grid. This parameter can be a value of @ref Segment codes
 */
void TM1637_SetChar(uint8_t left, uint8_t right)
{
    Set_AutoIncrease_DataCommand();
    Set_AddressCommand(TM1637_GRID1);
    Set_DisplayData(left, right);
}

/**
 * @brief Set the brightness of the TM1637 display
 * @param brightness The brightness level. This parameter can be a value of @ref TM1637_Brightness
 * @param on The display on/off state. This parameter can be a value of @ref TM1637_DisplayState
 */
void TM1637_SetBrightness(uint8_t brightness, uint8_t on)
{
    Set_DisplayControl(brightness, on);
}

static inline void TM1637_CLK_HIGH(void)
{
    HAL_GPIO_WritePin(TM1637_CLK_GPIO_Port, TM1637_CLK_Pin, GPIO_PIN_SET);
}

static inline void TM1637_CLK_LOW(void)
{
    HAL_GPIO_WritePin(TM1637_CLK_GPIO_Port, TM1637_CLK_Pin, GPIO_PIN_RESET);
}

static inline void TM1637_DIO_HIGH(void)
{
    HAL_GPIO_WritePin(TM1637_DIO_GPIO_Port, TM1637_DIO_Pin, GPIO_PIN_SET);
}

static inline void TM1637_DIO_LOW(void)
{
    HAL_GPIO_WritePin(TM1637_DIO_GPIO_Port, TM1637_DIO_Pin, GPIO_PIN_RESET);
}

static inline void Start(void)
{
    TM1637_DIO_HIGH();
    TM1637_CLK_HIGH();
    Delay_Us(2U);
    TM1637_DIO_LOW();
    Delay_Us(2U);
}

static inline void Stop(void)
{
    TM1637_CLK_LOW();
    TM1637_DIO_LOW();
    Delay_Us(2U);
    TM1637_CLK_HIGH();
    Delay_Us(2U);
    TM1637_DIO_HIGH();
    Delay_Us(2U);
}

static GPIO_PinState TM1637_WriteByte(uint8_t data)
{
    TM1637_CLK_LOW();
    for (uint32_t i = 0; i < 8; i++)
    {
        uint8_t bit = (data & (1 << i)) == 0 ? 0 : 1;

        if (bit == 1)
        {
            TM1637_DIO_HIGH();
        }
        else
        {
            TM1637_DIO_LOW();
        }
        Delay_Us(2U);
        TM1637_CLK_HIGH();
        Delay_Us(2U);
        TM1637_CLK_LOW();
    }
    /* 释放 DIO */
    TM1637_DIO_HIGH();
    Delay_Us(2U);

    TM1637_CLK_HIGH();
    Delay_Us(2U);
    GPIO_PinState ack = HAL_GPIO_ReadPin(TM1637_DIO_GPIO_Port, TM1637_DIO_Pin);
    TM1637_CLK_LOW();
    return ack;
}

static inline void Set_AutoIncrease_DataCommand(void)
{
    Start();
    (void) TM1637_WriteByte(0x40);
    Stop();
}

static inline void Set_AddressCommand(uint8_t address)
{
    Start();
    (void) TM1637_WriteByte(0xC0 | (address & 0x07));
}

static inline void Set_DisplayData(uint8_t left, uint8_t right)
{
    (void) TM1637_WriteByte(left);
    (void) TM1637_WriteByte(right);
    Stop();
}

static inline void Set_DisplayControl(uint8_t brightness, uint8_t on)
{
    Start();
    (void) TM1637_WriteByte(0x80 | (brightness & TM1637_DUTY_14_16) | (on ? TM1637_DISPLAY_ON : TM1637_DISPLAY_OFF));
    Stop();
}