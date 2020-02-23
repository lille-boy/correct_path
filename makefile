CC = gcc
CFLAGS = -I.
DEPS = correct_path.h tests.h
OBJ = main.o correct_path.o tests.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

correct_path: $(OBJ)
	$(CC) -o  $@ $^ $(CFLAGS)
