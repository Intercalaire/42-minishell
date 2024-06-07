# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgodart <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/03 11:38:34 by vgodart           #+#    #+#              #
#    Updated: 2024/05/02 14:56:08 by vgodart          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Basic variables
NAME = minishell
CC = clang
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f
CLEAR = clear

# Files
SRC	= ./src/parsing_test/init.c \
		./src/parsing_test/parsing.c \
		./src/parsing_test/utils.c \
		./src/parsing_test/ft_free.c \
		./src/parsing_test/pars_pipe.c \
		./src/parsing_test/quote.c \
		./src/parsing_test/special_char.c \
		./src/parsing_test/environment_variable.c \
		./src/parsing_test/check_pipe.c \
		./src/parsing_test/ft_strtok.c \
		./src/parsing_test/check_word.c \
		./src/exec/env.c \
		./src/exec/search_env.c \
		./src/exec/echo.c \
		./src/exec/exec.c \
		./src/exec/pwd.c \
		./src/exec/path.c \
		./src/exec/export.c \
		./src/exec/unset.c \
		./src/exec/cd.c \

OBJ	= $(SRC:.c=.o)

# Libft
LIBFT_PATH	= ./Libft
LIBFT_NAME	= ./Libft/Libft.a

# Compilation
all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_PATH)
	@$(CC) -lreadline $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT_NAME)

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT_PATH)

re: fclean all	

.PHONY: all clean fclean re
