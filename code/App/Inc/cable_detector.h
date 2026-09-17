#ifndef CABLE_DETECTOR_H
#define CABLE_DETECTOR_H

#include <stdint.h>

typedef enum
{
    CABLE_DETECT_NONE = 0,
    CABLE_DETECT_SINGLE,
    CABLE_DETECT_MULTIPLE
} CableDetectStatus;

typedef struct
{
    CableDetectStatus status;
    uint8_t channel;
    uint8_t active_count;
} CableDetectResult;

/*
 * 将 HC165_ReadRaw() 返回的原始位流解析为排线检测结果。
 *
 * channel 仅在 status 为 CABLE_DETECT_SINGLE 时有效，范围为 1~50；
 * 其余状态下 channel 为 0。
 */
CableDetectResult CableDetector_Decode(uint64_t raw_data);

#endif /* CABLE_DETECTOR_H */
