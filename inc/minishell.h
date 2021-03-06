/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:04:55 by psaulnie          #+#    #+#             */
/*   Updated: 2022/05/30 11:26:52 by psaulnie         ###   ########.fr       */
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
# include <sys/stat.h>

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
	t_list_char	*start;
	t_list_char	*addon_env;
	int			len_env;
	int			error_code;
	int			limiter_check;
}				t_env;

typedef struct s_pipe
{
	int	in;
	int	out;
}				t_pipe;

typedef struct s_data
{
	int			old_stdin;
	int			old_stdout;
	int			p[2];
	int			fdd[2];
	int			old_fd;
	int			has_redirection;
	pid_t		pid;
	t_env		*env;
	t_list_char	*cmd;
	t_list_char	*start;
	t_pipe		pipes[2];
	struct stat	stat;
}				t_data;

//miltn -> man i love the norm :D jk

typedef struct s_miltn
{
	char		*line;
	t_list_char	*start;
	t_list_char	*tmp;
	t_list_char	*new_link;
	t_list_char	*freeable;
}				t_miltn;

typedef struct s_here_doc
{
	char	*limiter;
	int		tmp_file_fd;
	int		stdin_cpy;	
}				t_here_doc;

typedef struct s_ghm
{
	char	*new_str;
	char	c[2];
}				t_ghm;

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

void		split_redirection(t_list_char **cmd, t_env *env);

/*	SPLIT_REDIRECTION_UTILS.C	*/

char		*redirection_split(char *cmd);
t_index		skipper(t_index var, char *cmd);
int			type_setter(t_index var, t_list_char **cmd, t_list_char **start,
				int current);

/*	SPLIT_REDIRECTION_UTILS2.C	*/

int			iteration_nbr(char *cmd);
t_index		var_skipper(t_index var, t_list_char **cmd);
char		*trim_char(char *cmd);

/*****************************************
 *										 *
 *               EXECUTION               *
 * 										 *
 *****************************************/

/*	EXECUTION.C	*/

t_env		start_execution(t_list_char **cmd, t_env *env);
void		exec(char **cmd, t_env *env, t_data *data);

/*	EXEC_PIPE.C	*/

int			wait_loop(t_data *data);
int			execution_pipe(t_data *data);

/*	REDIRECTION.C	*/

int			redirection(t_data *data, int i);

/*	GET_PATH.C	*/

char		*get_envvar(t_env *env, char *var);
char		*get_path(t_env *env, char *cmd);

/*	HERE_DOC.C	*/

char		*write_buffer_in_file(int type, t_env *env, int fd, char *buffer);
int			here_doc(t_data *data, int current, char *buffer);

/*	HERE_DOC_UTILS.c	*/

void		double_rout(void);
char		*while_here_doc(t_data *data, char *buffer, t_here_doc *here_doc,
				int current);

/*	SPECIAL_CASE.C	*/

int			special_case(char **list, t_env *env);

/*	SPECIAL_CASE_UTILS1.C	*/

int			go_to(char **list, t_env *env);
char		*return_pwd(void);

/*	SPECIAL_CASE_UTILS2 + 3.C	*/

void		write_env(t_env *env);
int			export(char **list, t_env *env);
int			leave_this(char **list);
int			is_equal(char *str);
void		unset_this(t_env *env, char **list);

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