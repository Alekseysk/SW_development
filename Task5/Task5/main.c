#include <stdio.h>
#include <malloc.h>
#include "WindowFilter.h"
#include "stdint.h"

Window_flt_t window_buff;
uint8_t RawBuff;
uint8_t ResBuff;
uint16_t window_length = 20;
uint16_t buf_length = 50;

int main(void)
{
    WindowFilter_Init(&window_buff, &RawBuff, &ResBuff, window_length, buf_length);
    for (uint8_t i = 0; i < 40; ++i)
    {
        Value_Put(&window_buff, i+5);
        printf("%d %d\n", Values_GetCount(&window_buff), Value_Get(&window_buff));
    }



}

