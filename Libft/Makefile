# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgodart <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 13:20:19 by vgodart           #+#    #+#              #
#    Updated: 2023/11/01 16:28:59 by vgodart          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRC = ft_atoi.c \
	ft_bzero.c \
  	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_strchr.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putnbr_fd.c \
	ft_putendl_fd.c \
	ft_strtrim.c \
	ft_split.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_itoa.c \
	ft_printf.c \
	ft_putnbr_base_fd.c \
	ft_hexa_fd.c \
	get_next_line.c \
	get_next_line_utils.c \
	ft_strcmp.c \
	ft_utils_strdup.c \
	

OBJ = $(SRC:.c=.o)

NAME = Libft.a

BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c

BONUS_OBJ = $(BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(BONUS_OBJ)
	ar rcs $(NAME) $(OBJ) $(BONUS_OBJ)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME) 

re: fclean all

.PHONY: all clean fclean re
	
