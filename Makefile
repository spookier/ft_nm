NAME = ft_nm
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = ./srcs/
INCS_DIR = ./incs

LIBFT_DIR = ./libft/libft
PRINTF_DIR = ./libft/ft_printf
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(PRINTF_DIR)/libftprintf.a
LIB_INCS = -I $(LIBFT_DIR) -I $(PRINTF_DIR)/incs

FILES = $(SRC)main.c \
		$(SRC)init.c \
		$(SRC)handle64.c \
		$(SRC)handle32.c \
		$(SRC)utils.c \

OBJ_FILES = $(FILES:.c=.o)

.c.o:
		$(CC) $(CFLAGS) -c -o $@ $< -I $(INCS_DIR) $(LIB_INCS)

all: $(NAME)

$(LIBFT):
		$(MAKE) -C $(LIBFT_DIR)

$(PRINTF):
		$(MAKE) -C $(PRINTF_DIR)

$(NAME): $(LIBFT) $(PRINTF) $(OBJ_FILES)
		$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) $(PRINTF) -o $@

clean:
		$(MAKE) -C $(LIBFT_DIR) clean
		$(MAKE) -C $(PRINTF_DIR) clean
		rm -rf $(OBJ_FILES)

fclean: clean
		$(MAKE) -C $(LIBFT_DIR) fclean
		$(MAKE) -C $(PRINTF_DIR) fclean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
