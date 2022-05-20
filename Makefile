# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 12:17:01 by lbattest          #+#    #+#              #
#    Updated: 2022/05/20 16:46:14 by psaulnie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	minishell

DIR_SRCS	:=	srcs
DIR_OBJS	:=	.objs
DIR_INCS	:=	inc

CC		:=	gcc
LDFLAGS := -L/usr/include -lreadline -L $(HOME)/.brew/opt/readline/lib -Llibft -lft
CFLAGS	:=	-I $(DIR_INCS) -I $(HOME)/.brew/opt/readline/include -Wall -Wextra -Werror
# CFLAGS	+= -fsanitize=address -g3
# LDFLAGS += -fsanitize=address -g3

DIR_LIBFT	:=	libft

LST_SRCS	:=	main.c \
				get_path.c \
				special_case.c \
				special_case_utils1.c \
				special_case_utils2.c \
				utils.c \
				command_size_counter.c \
				command_splitter.c \
				ft_getenv.c \
				here_doc.c \
				here_doc_utils.c \
				parsing.c \
				parsing_utils.c \
				quote_remover.c \
				remove_useless_command.c \
				replace_env_var.c \
				replace_env_var_exit_status.c \
				split_redirection.c \
				split_redirection_utils.c \
				split_redirection_utils2.c \
				check_and_clean_parsing.c \
				execution.c \
				exec_pipe.c \
				mod_envp.c \
				mod_envp2.c \
				redirection.c \

LST_OBJS	:=	$(LST_SRCS:.c=.o)

LST_INCS	:=	minishell.h

SRCS	:=	$(addprefix $(DIR_SRCS)/,$(LST_SRCS))
OBJS	:=	$(addprefix $(DIR_OBJS)/,$(LST_OBJS))
INCS	:=	$(addprefix $(DIR_INCS)/,$(LST_INCS))


AR_LIBFT	:=	$(DIR_LIBFT)/libft.a

all:	lib $(NAME)

$(NAME):	$(AR_LIBFT) $(OBJS)
		$(CC) $(LDFLAGS) $^ -o $@

$(DIR_OBJS)/%.o:	$(DIR_SRCS)/%.c $(INCS) Makefile | $(DIR_OBJS)
		$(CC) $(CFLAGS) -c $< -o $@

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