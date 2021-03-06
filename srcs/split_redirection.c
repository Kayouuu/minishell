/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:11:59 by psaulnie          #+#    #+#             */
/*   Updated: 2022/05/25 16:02:28 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
	Split the command in the array
	Example : [echo a > test b] ---> [echo a b] => [3] [test]
*/

static t_index	splitter_process(t_list_char **cmd,
		t_index var, int c)
{
	var.k = var.i;
	while (var.k < (int)ft_strlen((*cmd)->content) && (*cmd)->content[var.k]
		&& ((*cmd)->content[var.k] == '<' || (*cmd)->content[var.k] == '>'))
		var.k++;
	var.k = skip_whitespace((*cmd)->content, var.k);
	var.j = var.k;
	if (var.j < (int)ft_strlen((*cmd)->content)
		&& ((*cmd)->content[var.j] == '"' || (*cmd)->content[var.j] == '\''))
	{
		var.quote = (*cmd)->content[var.j];
		var.j++;
		while ((*cmd)->content[var.j] && (*cmd)->content[var.j] != var.quote)
			var.j++;
		var.j++;
	}
	while (var.j < (int)ft_strlen((*cmd)->content) && (*cmd)->content[var.j - 1]
		&& (*cmd)->content[var.j] && !ft_iswhitespace((*cmd)->content[var.j])
		&& (*cmd)->content[var.j] != '|' && (*cmd)->content[var.j] != '>'
		&& (*cmd)->content[var.j] != '<')
		var.j++;
	(*cmd)->redirection_file[c] = ft_stridup((*cmd)->content, var.k, var.j);
	if (var.j < (int)ft_strlen((*cmd)->content)
		&& ((*cmd)->content[var.j] == '<' || (*cmd)->content[var.j] == '>'))
		var.j--;
	return (var);
}

static void	splitter_loop(t_list_char **start, t_list_char **cmd,
		int iteration, int current)
{
	t_index		var;

	while ((*cmd)->content != NULL && current < iteration)
	{
		var = var_skipper(var, cmd);
		(*cmd)->type[current] = type_setter(var, cmd, start, current);
		if ((*cmd)->type[current] == 0)
			iteration = 0;
		var = splitter_process(cmd, var, current);
		(*cmd)->content = ft_strcut((*cmd)->content, var.i, var.j);
		if (!(*cmd)->content || !(*cmd)->redirection_file[current])
		{
			lstclear_char(start, free);
			exit_error_msg("Malloc error");
		}
		if ((*cmd)->content[0] == '\0')
		{
			free((*cmd)->content);
			(*cmd)->content = NULL;
		}
		current++;
	}
	(*cmd)->type[current] = -1;
	(*cmd)->redirection_file[current] = NULL;
}

static void	splitter(t_list_char **start, t_list_char **cmd)
{
	int			iteration;
	int			current;

	iteration = iteration_nbr((*cmd)->content);
	current = 0;
	(*cmd)->type = malloc(sizeof(int) * (iteration + 1));
	(*cmd)->redirection_file = malloc(sizeof(char *) * (iteration + 1));
	if (!(*cmd)->redirection_file || !(*cmd)->type)
	{
		ft_putendl_fd("Malloc error", 2);
		exit(0);
	}
	splitter_loop(start, cmd, iteration, current);
}

static t_data	init_data(t_env *env, t_list_char **cmd)
{
	t_data	data;

	data.old_stdin = dup(1);
	data.cmd = *cmd;
	data.start = *cmd;
	data.env = env;
	data.old_stdout = dup(0);
	dup2(data.old_stdout, 0);
	return (data);
}

void	split_redirection(t_list_char **cmd, t_env *env)
{
	t_data		data;
	t_list_char	*start;
	int			i;

	start = *cmd;
	while (*cmd != NULL)
	{
		(*cmd)->content = trim_char((*cmd)->content);
		splitter(&start, cmd);
		i = -1;
		while ((*cmd)->redirection_file[++i])
		{
			(*cmd)->redirection_file[i] = remove_quote(&start,
					(*cmd)->redirection_file[i]);
			data = init_data(env, cmd);
			if ((*cmd)->type[i] == 4 || (*cmd)->type[i] == 5)
				if (!here_doc(&data, i, NULL))
					break ;
		}
		(*cmd) = (*cmd)->next;
	}
	remove_useless_command(&start);
	*cmd = start;
	if (g_signal_flags)
		clear_list(&start);
}
