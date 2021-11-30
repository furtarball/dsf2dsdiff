#ifndef DSDIFF_H
#define DSDIFF_H
#include <stdint.h>
#include <stdio.h>
#include "dsf.h"

typedef struct {
    // I think it's OK to hardcode these values because
	// a DSF file can only contain so much metadata
	uint64_t PROPsize;
	uint64_t DSDsize;
	uint64_t FRM8size;
} dffinfo;

dffinfo init_dffinfo_struct(dsfinfo dsf);
void dff_channel_conf(char str[], dsfinfo dsf, char hr[]);

void write_header(FILE** outfile, dsfinfo dsf, dffinfo dff, char* channelStr);
void write_FRM8(FILE** outfile, uint64_t FRM8size);
void write_FVER(FILE** outfile);
void write_PROP(FILE** outfile, uint64_t PROPsize);
void write_FS(FILE** outfile, dsfinfo dsf);
void write_CHNL(FILE** outfile, dsfinfo dsf, char channelList[]);
void write_CMPR(FILE** outfile);

void write_DSD(FILE** infile, FILE** outfile, uint64_t DSDsize, dsfinfo dsf);
void convert_DSD_data(FILE** in, FILE** outfile, dsfinfo dsf);

#endif