objects = dsf2dsdiff.o endianness.o dsf.o dsdiff.o

dsf2dsdiff : $(objects)
	cc -o dsf2dsdiff $(objects)

dsf2dsdiff.o : dsf.h dsdiff.h dsf2dsdiff.h
endianness.o :
dsf.o : dsf.h dsf2dsdiff.h
dsdiff.o : dsdiff.h endianness.h

.PHONY : clean
clean :
	-rm $(objects) outfile*