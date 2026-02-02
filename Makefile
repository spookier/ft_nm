NAME = ft_nm
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
SRC = ./srcs/
INCS_DIR = ./incs

FILES = $(SRC)main.c \
		$(SRC)init.c \
		$(SRC)handle64.c \

OBJ_FILES = $(FILES:.c=.o)

.c.o:
		$(CC) $(CFLAGS) -c -o $@ $< -I $(INCS_DIR)

all: $(NAME)

$(NAME): $(OBJ_FILES)
		$(CC) $(CFLAGS) $^ -o $@ 

clean:
		rm -rf $(OBJ_FILES)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
