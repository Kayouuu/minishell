/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_and_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:41:10 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/21 16:54:16 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*dquote(char *cmd, int arg)
{
	char	*new_command;
	char	*command;
	t_index	index;
	char	quote;
	int		is_good;

	index.s_quote = 0;
	index.d_quote = 0;
	is_good = 0;
	if (arg == 0)
		quote = '\'';
	else if (arg == 1)
		quote = '"';
	new_command = NULL;
	new_command = ft_strjoin_gnl(new_command, "\n");
	if (!new_command)
	{
		// protection malloc
		exit(0);
	}
	while (1)
	{
		command = readline("> ");
		index.i = 0;
		while (command[index.i])
		{
			if (command[index.i] == quote)
				is_good ^= 1;
			index.i++;
		}
		new_command = ft_strjoin_gnl(new_command, command);
		if (!new_command)
		{
			// protection malloc
			exit(0);
		}
		free(command);
		if (is_good)
			break ;
		new_command = ft_strjoin_gnl(new_command, "\n");
		if (!new_command)
		{
			// protection malloc
			exit(0);
		}
	}
	cmd = ft_strjoin_gnl(cmd, new_command);
	if (!cmd)
	{
		// protection malloc
		exit(0);
	}
	free(new_command);
	return (cmd);
}

static t_index	change(char c, t_index i)
{
	if (c == '"')
	{
		if (i.quote == '0')
			i.quote = '"';
		else if (i.quote == '"')
			i.quote = '0';
		else
			i.quotes += 1;
		i.d_quote += 1;
	}
	else if (c == '\'')
	{
		if (i.quote == '0')
			i.quote = '\'';
		else if (i.quote == '\'')
			i.quote = '0';
		else
			i.quotes += 1;
		i.s_quote += 1;
	}
	return (i);
}

static int	count_size(char *cmd)
{
	t_index	index;
	int		i;

	index.s_quote = 0;
	index.d_quote = 0;
	index.quotes = 0;
	index.quote = '0';
	i = 0;
	while (cmd[i])
	{
		index = change(cmd[i], index);
		i++;
	}
	if (index.s_quote % 2 == 1)
		return (-1);
	if (index.d_quote % 2 == 1)
		return (-2);
	return (i + index.quotes);
}

static char	*remove_quote(t_list_char **start, char *cmd)
{
	t_index	index;
	char	*new_cmd;
	char	last_quote;
	int		last_quote_index;
	int		size;

	size = count_size(cmd);
	new_cmd = malloc(sizeof(char) * (size + 1));
	if (!new_cmd)
	{
		lstclear_char(start, free);
		ft_putendl_fd("Malloc error", 2);
		exit(0);
	}
	index.i = 0;
	index.j = 0;
	index.d_quote = 0;
	index.s_quote = 0;
	last_quote = '0';
	last_quote_index = -1;
	while (cmd[index.i])
	{
		if (last_quote == '0')
		{
			if (cmd[index.i] == '"')
				last_quote = '"';
			else if (cmd[index.i] == '\'')
				last_quote = '\'';
			if (last_quote != '0')
				last_quote_index = index.i;
		}
		if ((cmd[index.i] != '"' || last_quote != '"')
			&& (cmd[index.i] != '\'' || last_quote != '\''))
		{
			new_cmd[index.j] = cmd[index.i];
			index.j++;
		}
		else if (((cmd[index.i] == '"' && last_quote != '"')
				|| (cmd[index.i] == '\'' && last_quote != '\''))
			&& (last_quote == cmd[index.i]))
		{
			new_cmd[index.j] = cmd[index.i];
			index.j++;
		}
		if (last_quote == cmd[index.i] && last_quote_index != index.i)
			last_quote = '0';
		index.i++;
	}
	new_cmd[index.j] = '\0';
	return (new_cmd);
}

t_list_char	*replace_var_and_quote(t_list_char *cmd)
{
	t_list_char	**start;
	int			size;

	start = &cmd;
	while (cmd != NULL)
	{
		size = count_size(cmd->content);
		if (size == -1)
			cmd->content = dquote(cmd->content, 0);
		if (size == -2)
			cmd->content = dquote(cmd->content, 1);
		cmd->content = remove_quote(start, cmd->content);
		printf("[%s]\n", cmd->content);
		cmd = cmd->next;
	}
	return (*start);
}
