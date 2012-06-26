CC=gcc
CFLAGS=-Wall -Wextra -g
LFLAGS=-lGL -lGLU -lglut

all: exercise

exercise.o: exercise.c

exercise: exercise.o
	$(CC) $^ $(LFLAGS) -o $@

clean:
	rm exercise exercise.o
