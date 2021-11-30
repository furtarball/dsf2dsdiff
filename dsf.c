#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "dsf.h"
#include "endianness.h"
#include "dsf2dsdiff.h"

void check_dsf_headers(FILE** infile) {
  char DSDhead[4], fmtHead[4], dataHead[4];
  fread(&DSDhead, 4, 1, *infile);
  fseeko(*infile, 28, SEEK_SET);
  fread(&fmtHead, 4, 1, *infile);
	fseeko(*infile, 80, SEEK_SET);
	fread(&dataHead, 4, 1, *infile);
  ASSERT(!strncmp(DSDhead, "DSD ", 4) || !strncmp(fmtHead, "fmt ", 4) || !strncmp(dataHead, "data", 4),
		"Error: Not a valid DSF file");
  fseeko(*infile, 0, SEEK_SET);
}

dsfinfo dsfinfo_load(FILE** infile) {
	dsfinfo dsf;

	fseeko(*infile, 48, SEEK_SET);
	fread(&dsf.channelConf, 4, 1, *infile);
	fread(&dsf.channels, 4, 1, *infile);
	fread(&dsf.fs, 4, 1, *infile);
	fread(&dsf.bitdepth, 4, 1, *infile);
	fread(&dsf.samples, 8, 1, *infile);
	fread(&dsf.blockSize, 4, 1, *infile);

	dsfinfo_endianness(dsf);
	
	return dsf;
}

// in case it's not a little endian CPU
dsfinfo dsfinfo_endianness(dsfinfo dsf) {
	dsf.channelConf = le2h_u32(dsf.channelConf);
	dsf.channels = le2h_u32(dsf.channels);
	dsf.fs = le2h_u32(dsf.fs);
	dsf.bitdepth = le2h_u32(dsf.bitdepth);
	dsf.samples = le2h_u64(dsf.samples);
	dsf.blockSize = le2h_u32(dsf.blockSize);
	
	return dsf;
}

void check_dsf_metadata(dsfinfo dsf) {
	ASSERT(dsf.channelConf, "Error: Invalid channel configuration");
	ASSERT(dsf.channels, "Error: Number of channels set to zero");
	ASSERT(dsf.fs, "Error: Sample rate set to zero");
	ASSERT(dsf.bitdepth == 1, "Error: Bit depth different than 1");
	ASSERT(dsf.samples, "Error: Sample count is zero");
	if(dsf.blockSize != 4096) fputs("Warning: Block size different than 4096 (non-standard), continuing anyway\n", stderr);
}