# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O2

all	: bin/NTU_sort
	@echo -n ""

# optimized version
bin/NTU_sort	: sort_tool_opt.o main_opt.o lib
			$(CC) $(OPTFLAGS) sort_tool_opt.o main_opt.o -o bin/NTU_sort
main_opt.o 	   	: src/main.cpp
			$(CC) $(CFLAGS) $< -o $@
sort_tool_opt.o	: src/sort_tool.cpp src/sort_tool.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

# clean all the .o and executable files
clean:
		rm -rf *.o 

