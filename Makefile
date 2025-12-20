CC = gcc
CFLAGS = -Wall -g
TARGET = wordle
OBJS = main.o game.o solver.o utils.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c game.h solver.h utils.h
	$(CC) $(CFLAGS) -c main.c

game.o: game.c game.h
	$(CC) $(CFLAGS) -c game.c

solver.o: solver.c solver.h game.h
	$(CC) $(CFLAGS) -c solver.c

utils.o: utils.c utils.h game.h
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run