/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:26:08 by psaulnie          #+#    #+#             */
/*   Updated: 2022/04/11 12:20:08 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	start_execution(t_list_char **cmd, t_env *env)
{
	int			pid;
	int			time;
	t_list_char *cpy;

	time = 0;
	(void)env;
	while ((*cmd) != NULL)
	{
		if (time == 0 || !ft_memcmp((*cmd)->content, "|\0", 2))
		{
			pid = fork();
			if (pid == -1)
				error(0, "");
			time++;
		}
		if (pid == 0)
		{
			cpy = (*cmd)->next;
			if (cpy != NULL)
				redirection(cpy);
			exec(command_splitter((*cmd)->content), env);
		}
			// special_case((*cmd), env->envp);
		(*cmd) = (*cmd)->next;
	}
	while (wait(NULL) != -1)
		;
}
