/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:38:54 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/25 11:57:40 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	wait_loop(t_data *data)
{
	int	code;
	int	output;

	output = wait(&data->env->error_code);
	while (output != -1)
	{
		if (WIFEXITED(data->env->error_code))
		{
			code = WEXITSTATUS(data->env->error_code);
		}
		else if (WIFSIGNALED(data->env->error_code))
		{
			code = WTERMSIG(data->env->error_code) + 128;
		}
		output = wait(&data->env->error_code);
	}
	data->env->error_code = code;
	return (data->env->error_code);
}

static int	create_pipe(t_data *data)
{
	if (pipe(data->p) < 0)
		error(0, "");
	return (0);
}

static void	forking(t_data *data, int i)
{
	data->pid = fork();
	if (data->pid == -1)
		error(0, "");
	if (data->pid == 0)
	{
		if (!redirection(data, i))
			exit(1);
		if (!data->cmd->content)
			exit(1);
		data->env->error_code = special_case(
				command_splitter(data->cmd->content, &data->start), data->env);
		if (data->env->error_code >= 0)
			exit(data->env->error_code);
		exec(command_splitter(data->cmd->content, &data->start),
			data->env, data);
	}
}

static int	while_loop(t_data *data, int i)
{
	if (data->cmd->next && data->cmd->content
		&& !ft_memcmp(data->cmd->content, "|\0", 2))
		data->cmd = data->cmd->next;
	if (data->cmd->next && !ft_memcmp(data->cmd->next->content, "|\0", 2))
		if (create_pipe(data) == 1)
			return (data->env->error_code);
	if (g_signal_flags)
		return (data->env->error_code);
	forking(data, i);
	if (i > 0)
	{
		close(data->fdd[0]);
		close(data->fdd[1]);
	}
	ft_memcpy(data->fdd, data->p, sizeof(int) * 2);
	if (data->cmd && data->cmd->next)
		data->cmd = data->cmd->next;
	else
		return (-1);
	return (0);
}

int	execution_pipe(t_data *data)
{
	int	i;
	int	return_value;

	i = 0;
	while (data->cmd != NULL)
	{
		return_value = while_loop(data, i);
		if (return_value == -1)
			break ;
		else if (return_value > 0)
			return (data->env->error_code);
		i++;
	}
	data->env->error_code = wait_loop(data);
	return (data->env->error_code);
}
