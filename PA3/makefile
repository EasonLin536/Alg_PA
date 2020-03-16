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

all	: cb
	@echo -n ""

# optimized version
# mps	: src/main.cpp src/mps.cpp src/mps.h
# 	$(CC) $(OPTFLAGS) src/main.cpp src/mps.cpp -ltm_usage -Llib -o mps

cb			: cb_opt.o main_opt.o
	$(CC) $(OPTFLAGS) cb_opt.o main_opt.o -o cb
main_opt.o 	: src/main.cpp
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@
cb_opt.o	: src/cb.cpp src/cb.h
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

# clean all the .o and executable files
clean:
		rm -rf *.o *.out cb

