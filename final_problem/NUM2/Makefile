# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall

# the build target executable:
TARGET = SturmLiouville
HEADERS += FDMProblem.h \
	Solver.h \
	TridiagonalMatrix.h \
	Vector.h

SOURCES += SturmLiouville.cpp \
	Solver.cpp \
	TridiagonalMatrix.cpp \
	Vector.cpp


OBJECTS = $(SOURCES:.cpp=.o)

# define the executable file 
MAIN = SturmLiouville


.PHONY: depend clean

all:    $(MAIN)
	@echo  "*********\nSturmLiouville has been compiled and the executive file was placed in the directory 'bin/'.\n*********"

$(MAIN): $(OBJECTS) 
	$(CXX) $(CPPFLAGS) $(HEADERS) -o bin/$(MAIN) $(OBJECTS) $(LD_FLAGS)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXX_FLAGS) -c -o $@ $<

clean:
	$(RM) *.o *~ bin/$(MAIN) bin/*.txt


depend: $(SOURCES)
	makedepend $(HEADERS) $^

# DO NOT DELETE THIS LINE -- make depend needs it

