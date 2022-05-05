/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var_exit_status.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:00:53 by psaulnie          #+#    #+#             */
/*   Updated: 2022/05/05 10:40:00 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*env_var_replacing(t_index var, char *str, t_env env)
{
	char	*new_str;
	char	*exit_status;

	exit_status = ft_itoa(env.error_code);
	if (!exit_status)
	{
		free(var.new_cmd);
		exit_error_msg("Malloc error");
	}
	new_str = ft_strjoin_gnl(str, exit_status);
	free(exit_status);
	return (new_str);
}

char	*replace_env_var_exit_status(t_index var, char *cmd, t_env env)
{
	char	*new_str;
	char	c[2];

	var.can_replace = 1;
	c[1] = '\0';
	new_str = NULL;
	while (cmd[var.i])
	{
		c[0] = cmd[var.i];
		if (cmd[var.i] == '\'')
			var.can_replace ^= 1;
		if (cmd[var.i] == '$' && cmd[var.i + 1]
			&& cmd[var.i + 1] == '?' && var.can_replace)
		{
			var.i += 2;
			c[0] = cmd[var.i];
			new_str = env_var_replacing(var, new_str, env);
		}
		new_str = ft_strjoin_gnl(new_str, c);
		if (!new_str)
			exit_error_msg("Malloc error");
		var.i++;
	}
	free(var.new_cmd);
	return (new_str);
}
