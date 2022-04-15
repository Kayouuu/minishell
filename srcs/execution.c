/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:26:08 by psaulnie          #+#    #+#             */
/*   Updated: 2022/04/14 14:39:05 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	start_execution(t_list_char **cmd, t_env *env)
{
	t_data	data;

	data.old_stdin = dup(1);
	data.cmd = *cmd;
	data.start = *cmd;
	data.env = env;
	// if (lstsize_char(data.cmd) == 1)
	// {
	// 	data.pid = fork();
	// 	if (data.pid == -1)
	// 		error(0, "");
	// 	if (data.pid == 0)
	// 	{
	// 		special_case(command_splitter(data.cmd->content),
	// 			data.env->envp, &data.start);
	// 		exec(command_splitter(data.cmd->content), data.env);
	// 	}
	// 	wait(NULL);
	// }
	// else
		execution_pipe(&data);
}

void	execution_pipe(t_data *data)
{
	data->fdd = 0;
	while (data->cmd != NULL)
	{
		if (!ft_memcmp(data->cmd->content, "|\0", 2))
			if (pipe(data->p) < 0)
				error(0, "");
		data->pid = fork();
		if (data->pid == -1)
			error(0, "");
		if (data->pid == 0)
		{
			redirection(data);
			if (data->cmd && !ft_memcmp(data->cmd->content, "|\0", 2))
				data->cmd = data->cmd->next;
			if (data->cmd != NULL && data->cmd->next != NULL
				&& !ft_memcmp(data->cmd->next->content, ">\0", 2))
			{
				// dprintf(2, "{[%s]}\n", data->cmd->next->content);
				redirection(data);
			}
			special_case(command_splitter(data->cmd->content),
				data->env->envp, &data->start);
			exec(command_splitter(data->cmd->content), data->env);
			exit(0);
		}
		// if (close(data->p[1]) < 0)
		// 	error(0, "");
		data->fdd = data->p[0];
		data->cmd = data->cmd->next;
	}
	while (wait(NULL) != -1)
		;
}
