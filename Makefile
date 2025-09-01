# Compiler and flags
CC = gcc
CFLAGS = -std=c23 -Wall -Wextra -pedantic -Iinclude -fPIC -lm
DEBUG_FLAGS = -g
RELEASE_FLAGS = -O3
LDFLAGS = -shared # for dynamic lib

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
OBJ_DIR = ${BUILD_DIR}/obj
DEP_DIR = ${BUILD_DIR}/dep

# Path to install
INSTALL_DIR ?= /usr/local
INSTALL_DIR_INC = ${INSTALL_DIR}/include
INSTALL_DIR_LIB = ${INSTALL_DIR}/lib

# Srcs, objs and deps files
SRC = $(wildcard $(SRC_DIR)/estd/*.c) # All .c files in src/estd
OBJ = $(patsubst $(SRC_DIR)/estd/%.c, $(OBJ_DIR)/%.o, $(SRC))
DEP = $(patsubst $(SRC_DIR)/estd/%.c, $(DEP_DIR)/%.d, $(SRC))

# Targets
TARGET = estd
TARGET_STATIC = ${BUILD_DIR}/lib${TARGET}.a
TARGET_DYNAMIC = ${BUILD_DIR}/lib${TARGET}.so

# Mode(Default is debug) 
ifeq ($(release),1)
    CFLAGS += $(RELEASE_FLAGS)
else
    CFLAGS += $(DEBUG_FLAGS)
endif

.PHONY: all static dynamic install install_static install_dynamic clean

all: static

static: ${TARGET_STATIC}
dynamic: ${TARGET_DYNAMIC}

${TARGET_STATIC}: ${OBJ}
	mkdir -p ${@D}
	ar rcs $@ $^

${TARGET_DYNAMIC}: ${OBJ}
	mkdir -p ${@D}
	${CC} ${LDFLAGS} -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/estd/%.c
	mkdir -p $(@D) $(DEP_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@ -MT $@ -MF $(DEP_DIR)/$*.d

# include .d files
-include ${DEP}

clean:
	rm -rf ${BUILD_DIR} 

install: install_static install_dynamic

install_static: ${TARGET_STATIC}
	install -m 644 ${TARGET_STATIC}  ${INSTALL_DIR_LIB}
	install -d ${INSTALL_DIR_INC}/estd
	install -m 644 ${INC_DIR}/estd/*.h ${INSTALL_DIR_INC}/estd
	install -m 644 ${INC_DIR}/estd.h ${INSTALL_DIR_INC}

install_dynamic: ${TARGET_DYNAMIC}
	install -m 644 ${TARGET_DYNAMIC}  ${INSTALL_DIR_LIB}
	install -d ${INSTALL_DIR_INC}/estd
	install -m 644 ${INC_DIR}/estd/*.h ${INSTALL_DIR_INC}/estd
	install -m 644 ${INC_DIR}/estd.h ${INSTALL_DIR_INC}

uninstall:
	rm -f ${INSTALL_DIR_LIB}/libestd.*
	rm -f ${INSTALL_DIR_INC}/estd.h
	rm -rf ${INSTALL_DIR_INC}/estd 
