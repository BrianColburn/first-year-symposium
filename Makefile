CC=g++
CFLAGS=-std=c++11
BIN_NAME := microsOOFt
DEPS = location.h
OBJ = location.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

microsooft: $(OBJ)
	$(CC) -o $@ main.cpp $^ $(CFLAGS)
