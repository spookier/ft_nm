NAME = ft_nm
CC = cc
#CFLAGS = -Wall -Wextra -Werror -g3
CFLAGS = -g3

EXEC_DIR = ./src/exec/
PARSING_DIR = ./src/parsing/
BIN_DIR = ./bin/
INCS = ./include/

# Mandatory files
FILES = $(EXEC_DIR)ft_nm.c \
		$(PARSING_DIR)parsing.c \
		$(PARSING_DIR)e64_header_parse.c \
		$(PARSING_DIR)e32_header_parse.c \


OBJ_FILES = $(FILES:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCS)

$(BIN_DIR)$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

all: $(BIN_DIR)$(NAME)

clean :
	rm -f $(OBJ_FILES)

fclean : 
	make clean
	rm -rf $(BIN_DIR)$(NAME)

re: fclean
	make all

.PHONY: all clean fclean re