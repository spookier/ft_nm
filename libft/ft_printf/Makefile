# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acostin <acostin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/14 08:18:05 by acostin           #+#    #+#              #
#    Updated: 2022/12/17 00:26:20 by acostin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

# path for srcs
SRCS_DIR = ./srcs/
SRCS_UTILS_DIR = ./srcs/utils/

# path for header
INCS_DIR = ./incs

# Mandatory files
FILES =		$(SRCS_DIR)ft_printf.c \
			$(SRCS_DIR)print_all.c \
			$(SRCS_DIR)count_flags.c \
			$(SRCS_UTILS_DIR)utils_char.c \
			$(SRCS_UTILS_DIR)utils_str.c \
			$(SRCS_UTILS_DIR)utils_decimal.c \
			$(SRCS_UTILS_DIR)utils_unsigned_int.c \
			$(SRCS_UTILS_DIR)utils_hexa.c \
			$(SRCS_UTILS_DIR)utils_pointer.c \
			$(SRCS_UTILS_DIR)utils_padding.c \

# Transform .c files into .o
OBJ_FILES = $(FILES:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCS_DIR)


all : $(NAME)

$(NAME) : $(OBJ_FILES)
	ar rc $(NAME) $(OBJ_FILES)
	ranlib $(NAME)

# Clean all object files created
clean : 
	rm -rf $(OBJ_FILES)

# Clean all object files + the library created
fclean : clean
	rm -rf $(NAME)


#Fclean then build all
re : fclean
	make all


.PHONY : all clean fclean re