#ifndef HC165_H
#define HC165_H

#include <stdint.h>

#define HC165_CHIP_COUNT  7U
#define HC165_BIT_COUNT   (HC165_CHIP_COUNT * 8U)

/*
 * 读取 7 片级联 74HC165 的原始 56 位串行数据。
 *
 * 位与 CN1 线号的准确映射后续根据原理图确定；
 * 此函数本身只负责产生原始位流。
 */
uint64_t HC165_ReadRaw(void);

#endif /* HC165_H */