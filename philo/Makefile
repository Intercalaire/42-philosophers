# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgodart <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/03 11:38:34 by vgodart           #+#    #+#              #
#    Updated: 2024/04/10 12:50:20 by vgodart          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Basic variables
NAME = philo
CFLAGS = -Wall -Werror -Wextra -pthread
CC = cc
RM = rm -f
CLEAR = clear

# Files
SRC	= philosophers.c \
		parsing.c \
		supervisor.c \
		ft_calloc.c \
		ft_action.c \
		init.c \
		ft_routine.c \
		ft_routine_utils.c \
		time.c \

OBJ	= $(SRC:.c=.o)

# Compilation
all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all	

.PHONY: all clean fclean re
