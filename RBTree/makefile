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

all	: rbt
	@echo -n ""
rbt			: rbt_opt.o main_opt.o
	$(CC) bin/rbt_opt.o bin/main_opt.o -o bin/rbt
main_opt.o 	: src/main.cpp
	$(CC) $(CFLAGS) $< -o bin/$@
rbt_opt.o	: src/RBTree.cpp src/RBTree.h
	$(CC) $(CFLAGS) $< -o bin/$@

# clean all the .o and executable files
clean:
		rm -rf *.o *.out rbt

