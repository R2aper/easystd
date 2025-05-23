CC = gcc
CFLAGS = -Wall -Iinclude
# -L/usr/local/lib/libestd.a
LDFLAGS = -lestd -lcheck -lm -lpthread # todo
TARGET = tests

SRC = src/main.c
SRC_DIR = src
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
