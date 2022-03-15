# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/15 16:05:43 by psaulnie          #+#    #+#              #
#    Updated: 2022/03/15 17:04:14 by psaulnie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = srcs/main.c srcs/parsing.c
OBJS = ${SRCS:.c=.o}
CFLAGS = -Wall -Wextra -Werror
CC = gcc
NAME = minishell

.PHONY:	all clean fclean re

%.o:	%.c inc/minishell.h Makefile
		${CC} ${CFLAGS} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS} inc/minishell.h Makefile
		${CC} ${CFLAGS} ${OBJS} -o ${NAME} -lreadline

clean:
		rm -f ${OBJS}

fclean: clean
		rm -f ${NAME}

re: fclean all