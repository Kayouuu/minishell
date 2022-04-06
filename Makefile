# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 12:17:01 by lbattest          #+#    #+#              #
#    Updated: 2022/04/06 12:39:28 by lbattest         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	minishell

CC		:=	gcc
CSAN	:= -fsanitize=address -g3
CFLAGS	:=	-Wall -Wextra -Werror

DIR_SRCS	:=	srcs
DIR_OBJS	:=	.objs
DIR_INCS	:=	inc

DIR_LIBFT	:=	libft

LST_SRCS	:=	main.c \
				get_path.c \
				special_case.c \
				utils.c \
				add_to_envp.c \
				command_size_counter.c \
				command_splitter.c \
				exec.c \
				ft_getenv.c \
				parsing.c \
				parsing_utils.c \
				quote_remover.c \
				replace_var_and_quote.c \

LST_OBJS	:=	$(LST_SRCS:.c=.o)

LST_INCS	:=	minishell.h

SRCS	:=	$(addprefix $(DIR_SRCS)/,$(LST_SRCS))
OBJS	:=	$(addprefix $(DIR_OBJS)/,$(LST_OBJS))
INCS	:=	$(addprefix $(DIR_INCS)/,$(LST_INCS))


AR_LIBFT	:=	$(DIR_LIBFT)/libft.a

all:	lib $(NAME)

$(NAME):	$(AR_LIBFT) $(OBJS)
		$(CC) $(CFLAGS) $^ -o $@ -lreadline

$(DIR_OBJS)/%.o:	$(DIR_SRCS)/%.c $(INCS) Makefile | $(DIR_OBJS)
		$(CC) $(CFLAGS) -I  $(DIR_INCS) -c $< -o $@

$(DIR_OBJS):
		mkdir -p $(DIR_OBJS)

lib:
		make -C $(DIR_LIBFT)

clean:
		rm -rf $(DIR_OBJS)
		make -C $(DIR_LIBFT) clean

fclean:	clean
		rm -rf $(NAME)
		make -C $(DIR_LIBFT) fclean

re: fclean all

.PHONY:	all clean fclean re