/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var_exit_status.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:00:53 by psaulnie          #+#    #+#             */
/*   Updated: 2022/05/04 17:43:13 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*replace_env_var_exit_status(t_index var, char *cmd, t_env env)
{
	char	*str;
	char	*next;

	str = ft_itoa(env.error_code);
	var.j++;
	var.new_cmd = ft_strcut(cmd, var.i - 1, ft_strlen(cmd));
	next = ft_stridup(cmd, var.j, ft_strlen(cmd));
	var.new_cmd = ft_strjoin_gnl(var.new_cmd, str);
	var.new_cmd = ft_strjoin_gnl(var.new_cmd, next);
	free(str);
	var.i += 2;
	var.j += 2;
	free(cmd);
	cmd = ft_strdup(var.new_cmd);
	return (var.new_cmd);
}
