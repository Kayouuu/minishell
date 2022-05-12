/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:04:55 by psaulnie          #+#    #+#             */
/*   Updated: 2022/05/12 11:18:57 by lbattest         ###   ########.fr       */
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

/*
	SINGLE_RIN : >
	DOUBLE_RIN : >>
	SINGLE_ROUT : <
	DOUBLE_ROUT : <<
	DOUBLE_ROUT_PARTICULAR : << with a quoted filename
*/

# define NONE 0
# define SINGLE_RIN 1
# define DOUBLE_RIN 2
# define SINGLE_ROUT 3
# define DOUBLE_ROUT 4
# define DOUBLE_ROUT_PARTICULAR 5

typedef struct s_index
{
	int		i;
	int		j;
	int		k;
	int		s_quote;
	int		d_quote;
	char	quote;
	int		quotes;
	int		can_replace;
	char	last_quote;
	int		last_quote_index;
	char	*new_cmd;
	char	*var_name;
	int		is_exit_status;
}	t_index;

typedef struct s_env
{
	char		**envp;
	t_list_char	*addon_env;
	int			len_env;
	int			error_code;
	int			limiter_check;
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

int	g_signal_flags;

/*****************************************
 *										 *
 * 				  PARSING                *
 * 										 *
 *****************************************/

/*	MOD_ENVP	*/

void		env_tab_to_list(char **envp, t_env *env);
char		**env_list_to_tab(t_env *env);

/*	MOD_ENVP2	*/

void		env_replace_line(t_env **env, char *var, char *value);
void		env_remove_line(t_env *env, char *line);

/*	CHECK_AND_CLEAN_PARSING.C	*/

int			check_and_clean_parsing(t_list_char **cmd);

/*	COMMAND_SIZE_COUNTER.C	*/

int			count_size(char *cmd);

/*	COMMAND_SPLITTER.C		*/

int			ft_iswhitespace(char c);
char		**command_splitter(char *cmd, t_list_char **start);

/*	DQUOTE.C	*/

char		*dquote(char *cmd, int arg);

/*	FT_GETENV.C	*/

char		*ft_getenv(t_env env, char *name);

/*	PARSING.C	*/

t_list_char	*parsing(char *cmd);

/*	PARSING_UTILS.C	*/

int			skip_whitespace(char *cmd, int i);
int			is_useless(char *command);

/*	QUOTE_REMOVER.C	*/

char		*remove_quote(t_list_char **start, char *cmd);

/*	REMOVE_USELESS_COMMAND.C	*/

void		remove_useless_command(t_list_char **cmd);

/*	REPLACE_ENV_VAR_REDIRECTION	*/

void		replace_env_var_redirection(t_list_char **start, t_list_char **cmd);

/*	REPLACE_VAR_AND_QUOTE.C	*/

char		*replace_env_var(char *cmd, t_env env);
void		replace_var_and_quote(t_list_char **cmd);

/*	REPLACE_ENV_VAR_EXIT_STATUS.C	*/

char		*replace_env_var_exit_status(t_index var, char *cmd, t_env env);

/*	SPLIT_REDIRECTION.C	*/

void		split_redirection(t_list_char **cmd);

/*	SPLIT_REDIRECTION_UTILS.C	*/

char		*redirection_split(char *cmd);
t_index		skipper(t_index var, char *cmd);
int			type_setter(t_index var, t_list_char **cmd, t_list_char **start,
				int current);

/*	SPLIT_REDIRECTION_UTILS2.C	*/

int			iteration_nbr(char *cmd);
t_index		var_skipper(t_index var, t_list_char **cmd);

/*****************************************
 *										 *
 *               EXECUTION               *
 * 										 *
 *****************************************/

/*	ADD_TO_ENVP.C	*/

void		add_env(t_env *env, char *str);

/*	EXECUTION.C	*/

void		execution_pipe(t_data *data);
void		start_execution(t_list_char **cmd, t_env *env);

/*	EXEC.C	*/

void		redirection(t_data *data);
void		exec(char **cmd, t_env *env);

/*	EXEC_UTILS.C	*/

int			is_cmd_special(char *cmd);

/*	GET_PATH.C	*/

char		*get_envvar(t_env *env, char *var);
char		*get_path(t_env *env, char *cmd);

/*	HERE_DOC.C	*/

void		here_doc(t_data *data, int current);

/*	SPECIAL_CASE.C	*/

int			special_case(char **list, t_env *env);

/*****************************************
 *										 *
 *                 OTHER                 *
 * 										 *
 *****************************************/

/*	MAIN.C	*/

void		clear_list(t_list_char **start);

/*	UTILS.C	*/

void		error(int i, char *str);
void		exit_error_msg(char *str);
void		*free_all(char **str);

#endif