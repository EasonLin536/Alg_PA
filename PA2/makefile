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

# optimized version
# mps	: src/main.cpp src/mps.cpp src/mps.h
# 	$(CC) $(OPTFLAGS) src/main.cpp src/mps.cpp -ltm_usage -Llib -o mps

mps			: mps_opt.o main_opt.o lib
	$(CC) $(OPTFLAGS) mps_opt.o main_opt.o -ltm_usage -Llib -o mps
main_opt.o 	: src/main.cpp lib/tm_usage.h
	$(CC) $(CFLAGS) $< -Ilib -o $@
mps_opt.o	: src/mps.cpp src/mps.h
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

lib: lib/libtm_usage.a

lib/libtm_usage.a: tm_usage.o
	$(AR) $(ARFLAGS) $@ $<
tm_usage.o: lib/tm_usage.cpp lib/tm_usage.h
	$(CC) $(CFLAGS) $<

# clean all the .o and executable files
clean:
		rm -rf *.o lib/*.a lib/*.o *.out

