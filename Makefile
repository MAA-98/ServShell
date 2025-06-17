CC = clang
CFLAGS = -Wall -Wextra -g
INCLUDES = -Iinclude
SRC = src/main.c src/shell.c
OBJ = $(SRC:.c=.o)
TARGET = shell

all: $(TARGET)

$(TARGET): src/main.o src/shell.o
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

src/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)
