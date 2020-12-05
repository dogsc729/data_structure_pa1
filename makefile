# CC and CFLAGS are varilables
CC = g++
CFLAGS = -s
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O2

# problem2 
bin/pgrk2 : src/main2.cpp
	$(CC) -std=c++11 $^ -o $@
#problem1
bin/pgrk1 : src/main1.cpp
	$(CC) -std=c++11 $^ -o $@
#problem3
bin/pgrk3 : src/main3.cpp
	$(CC) -std=c++11 $^ -o $@



# clean all the .o and executable files
clean:
		rm -rf *.o lib/*.a lib/*.o bin/*

