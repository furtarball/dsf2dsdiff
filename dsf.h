#ifndef DSF_H
#define DSF_H
#include <stdint.h>
#include <stdio.h>

typedef struct {
	uint32_t channelConf;
	uint32_t channels;
	uint32_t fs;
	uint32_t bitdepth;
	uint64_t samples;
	uint32_t blockSize; // just in case
} dsfinfo;

dsfinfo dsfinfo_load(FILE** infile);
dsfinfo dsfinfo_endianness(dsfinfo dsf);
void check_dsf_headers(FILE** infile);
void check_dsf_metadata(dsfinfo dsf);

#endif