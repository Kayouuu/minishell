/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:26:08 by psaulnie          #+#    #+#             */
/*   Updated: 2022/05/21 18:57:35 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*check_pipe(t_data *data, char **cmd, t_env *env)
{
	char	*tmp;

	fstat(data->p[1], &data->stat);
	if ((unsigned int)data->stat.st_size >= 65536)
		close(data->p[1]);
	if (ft_strnstr(cmd[0], "minishell\0", ft_strlen(cmd[0])) != NULL)
		g_signal_flags = 1;
	tmp = get_path(env, cmd[0]);
	if (tmp == NULL)
	{
		ft_putendl_fd("minishell: Unable to find a path for the command\n", 2);
		exit(127);
	}
	return (tmp);
}

static void	signalhandler(int status)
{
	if (g_signal_flags && status != SIGQUIT)
		printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

static int	one_cmd(t_data *data)
{
	if (!redirection(data, 0))
		return (1);
	if (g_signal_flags || data->cmd->content == NULL)
		return (1);
	data->env->error_code = special_case(command_splitter(data->cmd->content,
				&data->start), data->env);
	if (data->env->error_code == -1)
	{
		data->pid = fork();
		if (data->pid == -1)
			error(0, "");
		if (data->pid == 0)
			exec(command_splitter(data->cmd->content, &data->start),
				data->env, data);
		data->env->error_code = wait_loop(data);
	}
	dup2(data->old_stdin, 1);
	return (data->env->error_code);
}

t_env	start_execution(t_list_char **cmd, t_env *env)
{
	t_data	data;

	signal(SIGINT, signalhandler);
	signal(SIGQUIT, signalhandler);
	data.old_stdin = dup(1);
	data.cmd = *cmd;
	data.start = *cmd;
	data.env = env;
	data.has_redirection = 0;
	data.old_stdout = dup(0);
	if (lstsize_char(data.cmd) == 1)
		data.env->error_code = one_cmd(&data);
	else
		execution_pipe(&data);
	dup2(data.old_stdout, 0);
	dup2(data.old_stdout, 1);
	return (*data.env);
}

void	exec(char **cmd, t_env *env, t_data *data)
{
	char	*tmp;

	if (!cmd && ((!cmd[0] || cmd[0] == '\0') || (!ft_memcmp(cmd[0], "<\0", 2)
				|| !ft_memcmp(cmd[0], "<<\0", 3) || !ft_memcmp(cmd[0], ">\0", 2)
				|| !ft_memcmp(cmd[0], ">>\0", 3)
				|| !ft_memcmp(cmd[0], "|\0", 2))))
	{
		free_all(cmd);
		exit(0);
	}
	tmp = check_pipe(data, cmd, env);
	free(cmd[0]);
	cmd[0] = tmp;
	env->envp = env_list_to_tab(env);
	if (data->cmd->next == NULL && !data->has_redirection)
		dup2(data->old_stdin, 1);
	if (execve(cmd[0], cmd, env->envp) < 0)
	{
		free_all(cmd);
		error(0, "");
	}
	exit(0);
}
