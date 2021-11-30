#include <stdint.h>

// Convert native endianness to big endian
uint64_t be_u64(uint64_t value) {
	static uint64_t be = 0;
	uint8_t* ptr = (uint8_t*)&be;
	for(int i = 7; i >= 0; i--) {
		ptr[i] = (value & 0xff);
		value >>= 8;
	}
	return be;
}
uint32_t be_u32(uint32_t value) {
	static uint32_t be = 0;
	uint8_t* ptr = (uint8_t*)&be;
	for(int i = 3; i >= 0; i--) {
		ptr[i] = (value & 0xff);
		value >>= 8;
	}
	return be;
}
uint16_t be_u16(uint16_t value) {
	static uint16_t be = 0;
	uint8_t* ptr = (uint8_t*)&be;
	for(int i = 1; i >= 0; i--) {
		ptr[i] = (value & 0xff);
		value >>= 8;
	}
	return be;
}

// Convert little endian to native
uint32_t le2h_u32(uint32_t value) {
	uint8_t* ptr = (uint8_t*)&value;
	uint32_t h = 0;
	for(int i = 0; i <= 3; i++) {
		h |= ptr[i] << 8 * i;
	}
	return h;
}
uint64_t le2h_u64(uint64_t value) {
	uint8_t* ptr = (uint8_t*)&value;
	uint64_t h = 0;
	for(int i = 0; i <= 7; i++) {
		h |= ptr[i] << 8 * i;
	}
	return h;
}