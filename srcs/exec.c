/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:04:40 by lbattest          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/04/04 13:54:51 by lbattest         ###   ########.fr       */
=======
/*   Updated: 2022/04/05 14:40:36 by psaulnie         ###   ########.fr       */
>>>>>>> 5d4c46bb76ed01f9b79ca4d8edaab543dcb59178
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
