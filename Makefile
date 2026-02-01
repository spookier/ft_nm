NAME		= ft_nm
CC		= cc
CFLAGS		= -Wall -Werror -Wextra -g3

SRC		= ./srcs/
INCS_DIR	= ./incs

INCS		= $(INCS_DIR)/ft_nm.h

FILES		= $(SRC)main.c \

OBJ_FILES	= $(FILES:.c=.o)

.c.o: $(INCS)
			$(CC) $(CFLAGS) -c -o $@ $< -I $(INCS_DIR)

all: $(NAME)

$(NAME): $(OBJ_FILES)
			$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME) -I $(INCS_DIR)

clean:
			rm -rf $(OBJ_FILES)

fclean: clean
			rm -rf $(NAME)

re: fclean
			$(MAKE) all

.PHONY: all clean fclean re
