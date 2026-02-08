# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acostin <acostin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 14:13:22 by acostin           #+#    #+#              #
#    Updated: 2022/12/15 18:02:38 by acostin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
NAME = libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra

# Mandatory files
FILES = ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_tolower.c \
	ft_strcmp.c \


# Transform .c files into .o
OBJ_FILES = $(FILES:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ_FILES)
	$(CC) $(CFLAGS) -c $(FILES)
	ar rc $(NAME) $(OBJ_FILES)
	ranlib $(NAME)


# Clean all object files created
clean : 
	rm -rf $(OBJ_FILES)

# Clean all object files + the library created
fclean : clean
	rm -rf $(NAME)

# Delete everything then rebuild
re : fclean
	make all

.PHONY : all clean fclean re bonus