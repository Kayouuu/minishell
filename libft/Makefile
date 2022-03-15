# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 11:30:57 by psaulnie          #+#    #+#              #
#    Updated: 2022/01/08 15:06:06 by psaulnie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
ft_putnbr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c  ft_strmapi.c \
ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
get_next_line.c get_next_line_utils.c
OBJS = ${SRCS:.c=.o}
CFLAGS = -Wall -Wextra -Werror
CC = gcc
NAME = libft.a

%.o:	%.c libft.h Makefile
		${CC} ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS}
			ar -rcs ${NAME} ${OBJS}

all:	${NAME}

clean:
		rm -f ${OBJS}

fclean:	clean
		rm -f ${NAME}

re:		fclean all

.PHONY:	all clean fclean re