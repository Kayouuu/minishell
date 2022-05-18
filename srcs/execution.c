/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:26:08 by psaulnie          #+#    #+#             */
/*   Updated: 2022/05/18 12:05:50 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	check_pipe(t_data *data)
{
	fstat(data->p[1], &data->stat);
	if ((unsigned int)data->stat.st_size >= 65536)
		close(data->p[1]);
}

static void	signalhandler(int status)
{
	(void)status;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

static t_data	one_cmd(t_data data)
{
	redirection(&data, 0);
	if (g_signal_flags || data.cmd->content == NULL)
		return (data);
	if (special_case(command_splitter(data.cmd->content, &data.start),
			data.env) == 0)
	{
		data.pid = fork();
		if (data.pid == -1)
			error(0, "");
		if (data.pid == 0)
			exec(command_splitter(data.cmd->content, &data.start),
				data.env, &data);
		data.env->error_code = wait_loop(&data);
	}
	dup2(data.old_stdin, 1);
	return (data);
}

t_env	start_execution(t_list_char **cmd, t_env *env)
{
	t_data	data;

	signal(SIGINT, signalhandler);
	signal(SIGQUIT, SIG_IGN);
	data.old_stdin = dup(1);
	data.cmd = *cmd;
	data.start = *cmd;
	data.env = env;
	data.old_stdout = dup(0);
	if (lstsize_char(data.cmd) == 1)
		data = one_cmd(data);
	else
		execution_pipe(&data);
	dup2(data.old_stdout, 0);
	dup2(data.old_stdout, 1);
	return (*data.env);
}

void	exec(char **cmd, t_env *env, t_data *data)
{
	char	*tmp;

	if (cmd[0] && (!ft_memcmp(cmd[0], "<\0", 2) || !ft_memcmp(cmd[0], "<<\0", 3)
			|| !ft_memcmp(cmd[0], ">\0", 2) || !ft_memcmp(cmd[0], ">>\0", 3)
			|| !ft_memcmp(cmd[0], "|\0", 2)))
	{
		free_all(cmd);
		exit(0);
	}
	check_pipe(data);
	tmp = get_path(env, cmd[0]);
	if (tmp == NULL)
		error(1, "minishell: Unable to find a path for the command");
	free(cmd[0]);
	cmd[0] = tmp;
	env->envp = env_list_to_tab(env);
	if (data->cmd->next == NULL)
		dup2(data->old_stdin, 1);
	if (execve(cmd[0], cmd, env->envp) < 0)
	{
		free_all(cmd);
		error(0, "");
	}
	exit(0);
}
