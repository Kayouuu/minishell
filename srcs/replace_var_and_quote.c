/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_and_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:41:10 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/28 15:03:05 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
	Replace_env_var function : find $ and check if it need to be replaced (if 
	there's single/double quote), then find the name of the var wanted and copy
	the string char by char
 */
static void	check_malloc(t_list_char **start, char *malloced)
{
	if (!malloced)
	{
		lstclear_char(start, free);
		exit_error_msg("Malloc error");
	}
}

static t_index	skip_no_env_var(t_index var, char *cmd)
{
	var.j = var.i;
	while (cmd[var.j] != '\0' && (cmd[var.j] != '$'
			|| var.can_replace == 0))
	{
		if (cmd[var.j] == '\'')
			var.can_replace ^= 1;
		var.j++;
	}
	return (var);
}

static t_index	replace(t_index var, char *cmd, t_list_char **start)
{
	var.i = var.j;
	if (cmd[var.i] == '$' && var.can_replace)
	{
		var.i++;
		while (cmd[var.i] && ft_isalnum(cmd[var.i]))
			var.i++;
		var.var_name = ft_stridup(cmd, var.j + 1, var.i);
		if (!var.var_name)
		{
			lstclear_char(start, free);
			exit_error_msg("Malloc error");
		}
		var.new_cmd = ft_strjoin_gnl(var.new_cmd, getenv(var.var_name));
		if (!var.new_cmd)
		{
			free(var.var_name);
			lstclear_char(start, free);
			exit_error_msg("Malloc error");
		}
	}
	else if (cmd[var.i] && cmd[var.j])
		var.i++;
	return (var);
}

char	*replace_env_var(t_list_char **start, char *cmd)
{
	t_index	var;

	var.i = 0;
	var.can_replace = 1;
	var.new_cmd = NULL;
	while (cmd[var.i] != '\0')
	{
		var = skip_no_env_var(var, cmd);
		if (var.i != var.j)
		{
			var.new_cmd = ft_strjoin_gnl(var.new_cmd,
					ft_stridup(cmd, var.i, var.j));
			check_malloc(start, var.new_cmd);

		}
		var = replace(var, cmd, start);
	}
	var.new_cmd = ft_strjoin_gnl(var.new_cmd, "\0");
	check_malloc(start, var.new_cmd);
	free(cmd);
	return (var.new_cmd);
}

t_list_char	*replace_var_and_quote(t_list_char *cmd)
{
	t_list_char	**start;

	start = &cmd;
	while (cmd != NULL)
	{
		cmd->content = replace_env_var(start, cmd->content);
		//cmd->content = remove_quote(start, cmd->content);
		printf("[%s]\n", cmd->content);
		cmd = cmd->next;
	}
	return (*start);
}
