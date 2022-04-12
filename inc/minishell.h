/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:04:55 by psaulnie          #+#    #+#             */
/*   Updated: 2022/04/12 13:51:19 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_index
{
	int		i;
	int		j;
	int		s_quote;
	int		d_quote;
	char	quote;
	int		quotes;
	int		can_replace;
	char	last_quote;
	int		last_quote_index;
	char	*new_cmd;
	char	*var_name;
}	t_index;

typedef struct s_env
{
	char		**envp;
	t_list_char	*addon_env;
}				t_env;

typedef struct s_data
{
	int			old_stdin;
	int			p[2];
	int			fdd;
	pid_t		pid;
	t_env		*env;
	t_list_char	*cmd;
	t_list_char	*start;
}				t_data;

/*****************************************
 *										 *
 * 				  PARSING                *
 * 										 *
 *****************************************/

/*	COMMAND_SIZE_COUNTER.C	*/

int			count_size(char *cmd);

/*	COMMAND_SPLITTER.C		*/

int			ft_iswhitespace(char c);
char		**command_splitter(char *cmd);

/*	DQUOTE.C	*/

char		*dquote(char *cmd, int arg);

/*	PARSING.C	*/

t_list_char	*parsing(char *cmd);

/*	PARSING_UTILS.C	*/

int			skip_whitespace(char *cmd, int i);
int			is_useless(char *command);

/*	QUOTE_REMOVER.C	*/

char		*remove_quote(t_list_char **start, char *cmd);

/*	REMOVE_USELESS_COMMAND.C	*/

void		remove_useless_command(t_list_char **cmd);

/*	REPLACE_VAR_AND_QUOTE.C	*/

char		*replace_env_var(t_list_char **start, char *cmd);
void		replace_var_and_quote(t_list_char **cmd);

/*	SPLIT_REDIRECTION.C	*/

void		split_redirection(t_list_char **cmd);

/*	SPLIT_REDIRECTION_AND_FILENAME.C	*/

void		split_redirection_and_filename(t_list_char **cmd);

/*	SPLIT_REDIRECTION_AND_FILENAME_NEXT.C	*/

void		add_next(t_list_char **next_link, t_list_char **start,
				t_list_char **command);	

/*****************************************
 *										 *
 *               EXECUTION               *
 * 										 *
 *****************************************/

/*	START_EXECUTION.C	*/

void		start_execution(t_list_char **cmd, t_env *env);
char		*get_path(char **envp, char *cmd);
int			special_case(char **list, char **envp, t_list_char **start);
void		error(int i, char *str);
void		add_env(t_env *env, char *str);
void		execution_pipe(t_data *data);
void		exec(char **cmd, t_env *env);
void		redirection(t_list_char *cmd, t_data *data);

/*****************************************
 *										 *
 *                 OTHER                 *
 * 										 *
 *****************************************/

/*	UTILS.C	*/

void		exit_error_msg(char *str);
void		*free_all(char **str);

#endif