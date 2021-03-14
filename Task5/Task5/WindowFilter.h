#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include "RingBuffer.h"

    typedef struct
    {
        RING_buffer_t RawBuff;
        RING_buffer_t ResBuff;
        uint16_t window_length;
    } Window_flt_t;

    void Value_Put(Window_flt_t* filter, uint8_t value);

    int32_t Value_Get(Window_flt_t* filter);

    uint16_t Values_GetCount(Window_flt_t* filter);

    void ALL_Clear(Window_flt_t* filter); 

    RING_ErrorStatus_t WindowFilter_Init(Window_flt_t* filter, uint8_t* raw_buf, uint8_t* res_buf, uint16_t window_length, uint16_t buf_length);

#ifdef __cplusplus
}
#endif