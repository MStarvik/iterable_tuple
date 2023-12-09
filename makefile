CC = g++
CFLAGS = -std=c++17 -Os -s

parameters: parameters.cpp
	$(CC) $(CFLAGS) -o $@ $^
