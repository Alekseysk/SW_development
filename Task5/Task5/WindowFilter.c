#include <stdio.h>
#include "WindowFilter.h"
#include "stdint.h"
#include "math.h"

void Value_Put(Window_flt_t* filter, uint8_t value)
{
    RING_Put(&(filter->RawBuff), value);
    if (RING_GetCount(&(filter->RawBuff)) == filter->window_length)
    {
        uint8_t filt_val = RING_GetWindowSum(&(filter->RawBuff), filter->window_length);
        RING_Put(&(filter->ResBuff), filt_val);
    }
}

int32_t Value_Get(Window_flt_t* filter)
{
    int32_t result;
    if (Values_GetCount(filter) > 0) result = RING_Get(&(filter->ResBuff));
    else result = -1;
    return result;
}

uint16_t Values_GetCount(Window_flt_t* filter)
{
    return RING_GetCount(&(filter->ResBuff));
}

void ALL_Clear(Window_flt_t* filter)
{
    RING_Clear(&(filter->RawBuff));
    RING_Clear(&(filter->ResBuff));
}

RING_ErrorStatus_t WindowFilter_Init(Window_flt_t* filter, uint8_t* raw_buf, uint8_t* res_buf, uint16_t window_length, uint16_t buf_length)
{
    RING_ErrorStatus_t RingBuffErr = RING_Init(&(filter->RawBuff), raw_buf, (uint16_t) pow(2, ceil(log2(window_length * 2))));
    RING_ErrorStatus_t WindowBuffErr = RING_Init(&(filter->ResBuff), res_buf, buf_length); 
    filter->window_length = window_length;

    return ((RingBuffErr && WindowBuffErr) ? RING_SUCCESS : RING_ERROR);
}
