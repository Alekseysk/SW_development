#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>

typedef struct
{
    uint8_t* buffer;
    uint16_t idxIn;
    uint16_t idxOut;
    uint16_t size;
} RING_buffer_t;

typedef enum
{
    RING_ERROR = 0,      
    RING_SUCCESS = !RING_ERROR 
} RING_ErrorStatus_t;

RING_ErrorStatus_t RING_Init(RING_buffer_t* ring, uint8_t* buf, uint16_t size);

uint16_t RING_GetCount(RING_buffer_t* buf);

void RING_Clear(RING_buffer_t* buf);

void RING_Put(RING_buffer_t* buf, uint8_t symbol);

uint8_t RING_Get(RING_buffer_t* buf);

uint8_t RING_GetWindowSum(RING_buffer_t* ringbuf, uint16_t len);

int32_t RING_ShowValue(RING_buffer_t* buf, uint16_t symbolNumber);

#ifdef __cplusplus
}
#endif