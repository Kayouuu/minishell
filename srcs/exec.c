/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:04:40 by lbattest          #+#    #+#             */
/*   Updated: 2022/04/01 12:51:18 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exec(char **cmd, t_env *env)
{
	char	*tmp;

	tmp = get_path(env->envp, cmd[0]);
	if (tmp == NULL)
		error(1, "minishell: Unable to find a path for the command");
	free(cmd[0]);
	cmd[0] = tmp;
	if (execve(cmd[0], cmd, env->envp) < 0)
	{
		free_all(cmd);
		error(0, "");
	}
}