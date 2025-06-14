CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS = -lestd -lcheck -lm -lpthread  -lsubunit
TARGET = tests

SRC = $(wildcard $(SRC_DIR)/*.c) # All src/.c files
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC)) # all .c files changes into .o files


.PHONY: all clean create_dir 

all: create_dir $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
	$(CC) $(CFLAGS) -c $< -o $@

create_dir:
	mkdir -p obj

clean:
	rm -f $(TARGET)
	rm -rf ${OBJ_DIR}
