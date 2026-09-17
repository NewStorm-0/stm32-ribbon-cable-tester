#include "cable_detector.h"

#define CABLE_DETECTOR_CHANNEL_COUNT 50U
#define CABLE_DETECTOR_NO_CHANNEL    0U

static uint8_t CableDetector_IsChannelActive(uint64_t raw_data, uint8_t raw_bit)
{
    /* 各检测输入由 10 kOhm 电阻上拉，测试表笔接 TEST_GND，因此低电平表示导通。 */
    return (uint8_t) (((raw_data >> raw_bit) & 1ULL) == 0ULL);
}

CableDetectResult CableDetector_Decode(uint64_t raw_data)
{
    CableDetectResult result = {
        .status = CABLE_DETECT_NONE,
        .channel = CABLE_DETECTOR_NO_CHANNEL,
        .active_count = 0U,
    };

    for (uint8_t channel_index = 0U; channel_index < CABLE_DETECTOR_CHANNEL_COUNT;
         channel_index++)
    {
        if (CableDetector_IsChannelActive(raw_data, channel_index) != 0U)
        {
            result.active_count++;
            result.channel = channel_index + 1U;
        }
    }

    if (result.active_count == 1U)
    {
        result.status = CABLE_DETECT_SINGLE;
    }
    else if (result.active_count > 1U)
    {
        result.status = CABLE_DETECT_MULTIPLE;
        result.channel = CABLE_DETECTOR_NO_CHANNEL;
    }

    return result;
}
