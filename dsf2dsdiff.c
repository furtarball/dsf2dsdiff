#include "dsf.h"
#include "dsdiff.h"
#include "dsf2dsdiff.h"
#include <stdio.h>

// get duration in human-readable form
void duration_hr(char str[], dsfinfo dsf) {
	uint64_t samples = dsf.samples;
	uint64_t minutes = samples / dsf.fs / 60;
	samples -= minutes * 60 * dsf.fs;
	double seconds = (double)samples / dsf.fs;

	snprintf(str, 26, "%02i:%05.2lf", minutes, seconds);
}

int main(int argc, char** argv) {
	ASSERT(argv[1], "Error: No input file specified");
	ASSERT(argv[2], "Error: No output file specified");
	FILE* infile;
	ASSERT(infile = fopen(argv[1], "rb"), "Error: Couldn't open input file");
	
	check_dsf_headers(&infile); // make sure it's a dsf file
	dsfinfo dsf = dsfinfo_load(&infile);
	check_dsf_metadata(dsf); // could help in some cases of broken files

	dffinfo dff = init_dffinfo_struct(dsf);
	
	// generate a proper DSDIFF channel list, e.g. "SLFTSRGT" for stereo
	char channelStr[dsf.channels * 4 + 1];
	char channelStrHR[7];
	dff_channel_conf(channelStr, dsf, channelStrHR);

	printf("File %s: ", argv[1]);
	printf("%s, ", channelStrHR);
	double fsMHz = (double)dsf.fs / 1000000; // a bit simpler than printing "DSD64" etc.
	printf("%lf MHz, ", fsMHz);
	char duration[27] = {0};
	duration_hr(duration, dsf);
	puts(duration);
	
	printf("Writing to file %s...\n", argv[2]);
	FILE* outfile;
	ASSERT(outfile = fopen(argv[2], "wb"), "Error: Couldn't open file for writing");
	write_header(&outfile, dsf, dff, channelStr);
	write_DSD(&infile, &outfile, dff.DSDsize, dsf); // do the actual conversion

	fclose(infile);
	fclose(outfile);
	return 0;
}
