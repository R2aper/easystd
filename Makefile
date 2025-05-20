# Compile and flags 
CC = gcc
CFLAGS = -std=c23 -Wall -Wextra -pedantic -Iinclude -fPIC
DEBUG_FLAGS = -g
RELEASE_FLAGS = -O3
LDFLAGS = -shared # for dynamic lib

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
OBJ_DIR = obj

# Src and obj files 
SRC = $(wildcard $(SRC_DIR)/*.c) # All src/.c files
OBJ = $(patsubst $(SRC_DIR)/%.c, ${BUILD_DIR}/$(OBJ_DIR)/%.o, $(SRC)) # all .c files changes into .o files
TARGET_STATIC = libestd.a 
TARGET_DYNAMIC = libestd.so

# Mode(Default is debug) 
ifeq ($(release),1)
    CFLAGS += $(RELEASE_FLAGS)
else
    CFLAGS += $(DEBUG_FLAGS)
endif

.PHONY: all clean install

all: create_dir static

static: create_dir ${TARGET_STATIC}
dynamic: create_dir ${TARGET_DYNAMIC}

$(TARGET_STATIC): $(OBJ)
	ar rcs $(BUILD_DIR)/$@ $^
	ranlib $(BUILD_DIR)/$@   

# For dynamic lib 
$(TARGET_DYNAMIC): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o ${BUILD_DIR}/$@

${BUILD_DIR}/$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

create_dir:
	mkdir -p $(BUILD_DIR)/${OBJ_DIR}

clean:
	rm -rf ${BUILD_DIR} 

install: 
	install -m 644 ${BUILD_DIR}/libestd* /usr/local/lib/
	install -d /usr/local/include/libestd/
	install -m 644 $(INC_DIR)/*.h /usr/local/include/libestd

uninstall:
	rm -rf /usr/local/lib/libestd*
	rm -rf /usr/local/include/libestd
