/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:41:10 by psaulnie          #+#    #+#             */
/*   Updated: 2022/05/17 14:26:58 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
	Replace_env_var function : find $ and check if it need to be replaced (if 
	there's single/double quote), then find the name of the var wanted and copy
	the string char by char
 */

static void	check_malloc(char *malloced)
{
	if (!malloced)
		exit_error_msg("Malloc error");
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
	if (cmd[var.j] == '$' && ft_isalnum(cmd[var.j + 1]) == 0)
		var.j += 1;
	if (var.j > 0 && cmd[var.j - 1] == '$' && cmd[var.j] == '?')
	{
		var.j += 1;
		if (cmd[var.j] != '$' && cmd[var.j])
			while (cmd[var.j])
				var.j++;
	}
	return (var);
}

static t_index	replace(t_index var, char *cmd, t_env env)
{
	char	*env_var;

	var.i = var.j;
	if ((cmd[var.i] && cmd[var.i] == '$' && cmd[var.i + 1]
			&& cmd[var.i + 1] != '?') && var.can_replace)
	{
		var.i++;
		while (cmd[var.i] && ft_isalnum(cmd[var.i]))
			var.i++;
		var.var_name = ft_stridup(cmd, var.j + 1, var.i);
		if (!var.var_name)
			exit_error_msg("Malloc error");
		env_var = ft_getenv(env, var.var_name);
		var.new_cmd = ft_strjoin_gnl(var.new_cmd, env_var);
		if (env_var)
			free(env_var);
		if (!var.new_cmd)
			exit_error_msg("Malloc error");
	}
	else if (cmd[var.i] && cmd[var.j])
		var.i++;
	return (var);
}

char	*replace_env_var(char *cmd, t_env env)
{
	t_index	var;
	char	*str;

	var.i = 0;
	var.can_replace = 1;
	var.new_cmd = NULL;
	while (cmd != NULL && cmd[var.i] != '\0')
	{
		var = skip_no_env_var(var, cmd);
		if (var.i != var.j)
		{
			str = ft_stridup(cmd, var.i, var.j);
			var.new_cmd = ft_strjoin_gnl(var.new_cmd, str);
			free(str);
			check_malloc(var.new_cmd);
		}
		var = replace(var, cmd, env);
	}
	var.new_cmd = ft_strjoin_gnl(var.new_cmd, "\0");
	check_malloc(var.new_cmd);
	free(cmd);
	var.i = 0;
	var.new_cmd = replace_env_var_exit_status(var, var.new_cmd, env);
	return (var.new_cmd);
}
