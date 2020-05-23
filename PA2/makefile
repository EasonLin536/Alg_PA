# CC and CFLAGS are varilables
CC = g++ -std=c++11
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O3

all	: mps
	@echo -n ""

mps			: mps_opt.o main_opt.o
	$(CC) $(OPTFLAGS) mps_opt.o main_opt.o -o mps
main_opt.o 	: src/main.cpp
	$(CC) $(CFLAGS) $< -o $@
mps_opt.o	: src/mps.cpp src/mps.h
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

# clean all the .o and executable files
clean:
		rm -rf *.o lib/*.a lib/*.o *.out

