CC=gcc
CFLAGS=-Wall -Wextra -g
LFLAGS=-lGL -lGLU -lglut
OSXFLAGS=-fnested-functions
FRAMEWORKS=-framework GLUT -framework OpenGL -framework Cocoa

SYSNAME=$(shell uname -s)

.PHONY: all
all: exercise

exercise.o: exercise.c
ifeq ($(SYSNAME),Darwin)
	$(CC) $(CFLAGS) $(OSXFLAGS) -c $^ 
else
	$(CC) $(CFLAGS) -c $^
endif

exercise: exercise.o
ifeq ($(SYSNAME),Darwin)
	$(CC) $(FRAMEWORKS) $^ -o $@
else
	$(CC) $^ $(LFLAGS) -o $@
endif

.PHONY: clean
clean:
	rm exercise *.o
