CC = clang 						# set compiler to clang, macOS default
CFLAGS = -Wall -Wextra -g 		# set compiler flags: give warnings, extra warnings and debug info
INCLUDES = -Iinclude			# headers provided in the /include directory
SRC = src/main.c src/shell.c src/daemon.c	# list of source files
OBJ = $(SRC:.c=.o)				# convert source .c files to object .o files
TARGET = servsh					# name of compiled program

all: $(TARGET)

$(TARGET): src/main.o src/shell.o src/daemon.o
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

src/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)
