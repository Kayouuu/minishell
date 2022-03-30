# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/15 16:05:43 by psaulnie          #+#    #+#              #
#    Updated: 2022/03/30 18:04:27 by psaulnie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = srcs/main.c srcs/parsing.c srcs/parsing_utils.c \
srcs/replace_var_and_quote.c srcs/dquote.c srcs/quote_remover.c \
srcs/command_size_counter.c srcs/utils.c srcs/command_splitter.c \
srcs/ft_getenv.c
OBJS = ${SRCS:.c=.o}
LIBFT = libft
LIBFT_LIB = libft/libft.a
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
CC = gcc
NAME = minishell

.PHONY:	all clean fclean re

%.o:	%.c inc/minishell.h Makefile
		${CC} ${CFLAGS} -c $< -o $@

all: lib ${NAME}

${NAME}: ${OBJS} inc/minishell.h Makefile
		${CC} ${CFLAGS} ${OBJS} ${LIBFT_LIB} -o ${NAME} -lreadline

lib:
	make all -C ${LIBFT}

clean:
		rm -f ${OBJS}
		make -C libft clean

fclean: clean
		rm -f ${NAME}
		make -C libft fclean

re: fclean all