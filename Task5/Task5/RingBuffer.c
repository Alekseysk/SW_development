#include <stdio.h>
#include <malloc.h>
#include "RingBuffer.h"
#include "stdint.h"

/**
 * @defgroup control Функции управления буфером
 * @{
 */

 /**
 @function RING_Init − Инициализация буфера.
 @param RING_buffer_t *ring − Указатель на кольцевой буфер.
 @param uint8_t *buf − Указатель на буфер хранения.
 @param uint16_t size − Сколько элементов в буфере.
 @return RING_ErrorStatus_t Результат инициализации @ref RING_ErrorStatus_t
  */

RING_ErrorStatus_t RING_Init(RING_buffer_t* ring, uint8_t* buf, uint16_t size)
{
    ring->size = size;
    ring->buffer = buf;
    RING_Clear(ring);

    return (ring->buffer ? RING_SUCCESS : RING_ERROR);
}

/**
@function RING_GetCount − Количество полезных данных в буфере.
@param RING_buffer_t *buf − Указатель на кольцевой буфер.
@return uint16_t Количество полезных данных в буфере.
 */

uint16_t RING_GetCount(RING_buffer_t* buf)
{
    uint16_t retval = 0;
    if (buf->idxIn < buf->idxOut) retval = buf->size + buf->idxIn - buf->idxOut;
    else retval = buf->idxIn - buf->idxOut;
    return retval;
}

/**
@function RING_Clear − Очищает буфер.
@param RING_buffer_t *buf − Указатель на кольцевой буфер.
 */

void RING_Clear(RING_buffer_t* buf)
{
    buf->idxIn = 0;
    buf->idxOut = 0;
}

/** @} */

/**
 * @defgroup put Функции загрузки данных в буфер
 * @{
 */

 /**
 @function RING_Put − Загружает элемент в буфер.
 @param uint8_t symbol − Элемент для загрузки в буфер.
 @param RING_buffer_t *buf − Указатель на кольцевой буфер.
  */

void RING_Put(RING_buffer_t* buf, uint8_t symbol)
{
    buf->buffer[buf->idxIn++] = symbol;
    if (buf->idxIn >= buf->size) buf->idxIn = 0;
}

/** @} */

/**
 * @defgroup get Функции выгрузки данных из буфера
 * @{
 */

 /**
 @function RING_Get − Получает из буфера байт.
 @param RING_buffer_t *buf − Указатель на кольцевой буфер.
 @return uint8_t Значение полученого элемента.
  */

uint8_t RING_Get(RING_buffer_t* buf)
{
    uint8_t retval = buf->buffer[buf->idxOut++];
    if (buf->idxOut >= buf->size) buf->idxOut = 0;
    return retval;
}

/**
@function RING_GetBuffr − Заполняет элементами кольцевого буфера массив.
@param RING_buffer_t *ringbuf − Указатель на кольцевой буфер.
@param uint8_t *destination − Указатель на массив.
@param uint16_t len − количество получаемых элементов.
 */

uint8_t RING_GetWindowSum(RING_buffer_t* ringbuf, uint16_t len)
{
    uint32_t sum = RING_Get(ringbuf);
    uint16_t tlen = len - 1;
    while (tlen--) sum += RING_ShowValue(ringbuf, len-tlen);
    return sum / len;
}

/** @} */

/**
 * @defgroup other Другие функции
 * @ingroup pop
 * @{
 */

 /**
 @function RING_ShowSymbol − Показывает содержимое элемента без его удаления из буфера.
 @param RING_buffer_t *ringbuf − Указатель на кольцевой буфер.
 @param uint16_t symbolNumbe − Номер элемента.
 @return int32_t Значение полученого элемента. -1 если ошибка.
  */

int32_t RING_ShowValue(RING_buffer_t* buf, uint16_t valueNumber)
{
    uint32_t pointer = buf->idxOut + valueNumber;
    int32_t  retval = -1;
    if (valueNumber < RING_GetCount(buf))
    {
        if (pointer > buf->size) pointer -= buf->size;
        retval = buf->buffer[pointer];
    }
    return retval;
}

/** @} */

