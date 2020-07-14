TARGET = system_monitor
DEBUG           ?= 0
SRC_DIR		= ./src/
OBJ_DIR		= ./obj/
SRC_INC_DIR	= $(SRC_DIR)
GTK_INC_DIR	= /usr/include/gtk-3.0/gtk/

C_FILES		= 	main.c\
				helpFuncs.c\
				read.c\
				get.c\
				interface.c\

O_FILES		= $(addprefix $(OBJ_DIR), $(C_FILES:.c=.o))

DEFINES         := DEBUG=$(DEBUG)
CC              = gcc
FLAGS		= -Wall -Werror -Wextra
CFLAGS		= -O2 -std=gnu18 -fms-extensions
HEADER_FLAGS	= -I $(SRC_INC_DIR) -I $(GTK_INC_DIR)
GTK_FLAGS = `pkg-config --cflags --libs gtk+-3.0`

DEFINES  := $(addprefix -D,$(DEFINES))

.PHONY:	all clean tidy re

all: $(TARGET)

$(TARGET): $(O_FILES)
	$(CC) $(O_FILES) -o $(TARGET) $(GTK_FLAGS)
	@/bin/echo "-e" "\e[32;1m[system_monitor created]\e[0m"

$(O_FILES): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(FLAGS) $(HEADER_FLAGS) $(GTK_FLAGS) $(DEFINES)

clean:
	rm -f $(O_FILES)
	@/bin/echo "-e" "\e[35;1m[system_monitor cleaned]\e[0m"

tidy: clean
	rm -f $(TARGET)
	rm -Rf $(OBJ_DIR)
	@/bin/echo "-e" "\e[31m[system_monitor tidied]\e[0m"

re: tidy all

