# Compile and flags 
CC = gcc
CFLAGS = -std=c23 -Wall -Wextra -pedantic -Iinclude -fPIC
DEBUG_FLAGS = -g
RELEASE_FLAGS = -O3

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Src and obj files 
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))
TARGET = libestd.a   # For static lib 
# TARGET = libmylib.so  # For dynamic lib 

# Mode(Default is debug) 
ifeq ($(release),1)
    CFLAGS += $(RELEASE_FLAGS)
else
    CFLAGS += $(DEBUG_FLAGS)
endif

# For dynamic add:
# LDFLAGS = -shared

.PHONY: all clean install

all: $(BUILD_DIR) $(TARGET)

# build static lib 
$(TARGET): $(OBJ)
	ar rcs $(BUILD_DIR)/$@ $^
	ranlib $(BUILD_DIR)/$@   

# For dynamic lib (Uncomment)
# $(TARGET): $(OBJ)
#	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

#install: $(TARGET)
#	install -d /usr/local/lib/
#	install -m 644 $(TARGET) /usr/local/lib/
#	install -d /usr/local/include/mylib/
#	install -m 644 $(INC_DIR)/*.h /usr/local/include/mylib/
