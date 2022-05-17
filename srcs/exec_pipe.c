/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:38:54 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/17 16:33:13 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	wait_loop(t_data *data)
{
	int	code;
	int	output;

	printf("%d\n", data->env->error_code);
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
		redirection(data, i);
		if (special_case(command_splitter(data->cmd->content, &data->start),
				data->env) == 1)
			exit(1);
		exec(command_splitter(data->cmd->content, &data->start),
			data->env, data);
	}
}

static void	close_two(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	execution_pipe(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmd != NULL)
	{
		if (!ft_memcmp(data->cmd->content, "|\0", 2))
			data->cmd = data->cmd->next;
		if (data->cmd->next && !ft_memcmp(data->cmd->next->content, "|\0", 2))
			if (create_pipe(data) == 1)
				return ;
		if (g_signal_flags)
			return ;
		forking(data, i);
		if (i > 0)
			close_two(data->fdd);
		ft_memcpy(data->fdd, data->p, sizeof(int) * 2);
		if (data->cmd && data->cmd->next)
			data->cmd = data->cmd->next;
		else
			break ;
		i++;
	}
	dprintf(2, "d\n");
	wait_loop(data);
	if (unlink("/tmp/.minishell_heredoc") < 0)
		error(0, "");
}
