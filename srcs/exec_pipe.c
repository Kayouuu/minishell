/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:38:54 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/16 14:54:47 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	create_pipe(t_data *data)
{
	if (pipe(data->p) < 0)
		error(0, "");
	if (data->cmd->next)
		data->cmd = data->cmd->next;
	else
	{
		ft_putendl_fd("error pipe", 2);
		return (1);
	}
	return (0);
}

static void	forking(t_data *data)
{
	data->pid = fork();
	if (data->pid == -1)
		error(0, "");
	if (data->pid == 0)
	{
		if (data->cmd && !ft_memcmp(data->cmd->content, "|\0", 2))
			data->cmd = data->cmd->next;
		if (data->cmd != NULL && data->cmd->next != NULL
			&& !ft_memcmp(data->cmd->next->content, ">\0", 2))
			redirection(data);
		if (special_case(command_splitter(data->cmd->content, &data->start),
				data->env) == 1)
			return ;
		exec(command_splitter(data->cmd->content, &data->start),
			data->env, data);
	}
}

void	execution_pipe(t_data *data)
{
	data->fdd = 0;
	while (data->cmd != NULL)
	{
		if (!ft_memcmp(data->cmd->content, "|\0", 2))
			if (create_pipe(data) == 1)
				return ;
		redirection(data);
		if (g_signal_flags)
			return ;
		forking(data);
		dup2(data->old_stdin, 1);
		data->fdd = data->p[0];
		if (data->cmd->next)
			data->cmd = data->cmd->next;
		else
			break ;
	}
	while (wait(&data->env->error_code) != -1)
		;
}
