#ifndef ENDIANNESS_H
#define ENDIANNESS_H
#include <stdint.h>

uint64_t be_u64(uint64_t value);
uint32_t be_u32(uint32_t value);
uint16_t be_u16(uint16_t value);

uint64_t le2h_u64(uint64_t value);
uint32_t le2h_u32(uint32_t value);

#endif
