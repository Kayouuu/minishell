/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var_exit_status.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:00:53 by psaulnie          #+#    #+#             */
/*   Updated: 2022/05/21 13:51:22 by psaulnie         ###   ########.fr       */
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

static void	while_loop(t_ghm *data, char *cmd, t_index *var, t_env env)
{
	data->c[0] = cmd[var->i];
	if (cmd[var->i] == '\'')
		var->can_replace ^= 1;
	if (cmd[var->i] == '$' && cmd[var->i + 1]
		&& cmd[var->i + 1] == '?' && var->can_replace)
	{
		var->i += 2;
		data->c[0] = cmd[var->i];
		if (cmd[var->i] == '$' && cmd[var->i + 1] && cmd[var->i + 1] == '?')
			data->c[0] = '\0';
		data->new_str = env_var_replacing(*var, data->new_str, env);
	}
	data->new_str = ft_strjoin_gnl(data->new_str, data->c);
	if (!data->new_str)
		exit_error_msg("Malloc error");
	if (cmd[var->i] == '$' && cmd[var->i + 1] && cmd[var->i + 1] == '?')
		var->i--;
}

char	*replace_env_var_exit_status(t_index var, char *cmd, t_env env)
{
	t_ghm	data;

	var.i = -1;
	var.can_replace = 1;
	data.c[1] = '\0';
	data.new_str = NULL;
	while (++var.i <= (int)ft_strlen(cmd) && cmd[var.i])
		while_loop(&data, cmd, &var, env);
	free(var.new_cmd);
	var.new_cmd = data.new_str;
	return (data.new_str);
}
