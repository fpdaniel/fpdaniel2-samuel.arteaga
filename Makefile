# Makefile - Document Index Creator

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wpedantic

PROG = a.out
SRCS = Main.cpp DocumentIndex.cpp GetLine.cpp
OBJS = $(SRCS:.cpp=.o)

$(PROG): $(OBJS)
	$(CXX) $(OBJS) -o $(PROG)

Main.o: Main.cpp DocumentIndex.h GetLine.h

DocumentIndex.o: DocumentIndex.cpp  DocumentIndex.h GetLine.h

GetLine.o: GetLine.cpp GetLine.h

.PHONY: clean
clean:
	rm *.o ActualIndex.txt a.out
