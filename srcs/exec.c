/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:04:40 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/09 12:09:04 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	redirection(t_data *data)
{
	int	fd;
	int	i;

	i = -1;
	while (data->cmd->type[++i] != -1)
	{
		dprintf(2, "[%d] - [%s]\n", data->cmd->type[i], data->cmd->redirection_file[i]);
		if (data->cmd->type[i] == SINGLE_RIN)
		{
			if (data->cmd->redirection_file[i] == NULL)
			{
				lstclear_char(&data->cmd, free);
				error(1, "minishell: syntax error near unexpected token `newline'");
			}
			fd = open(data->cmd->redirection_file[i], O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (fd < 0)
				error(0, "");
			if (dup2(fd, 1) < 0)
				error(0, "");
			if (close(fd) < 0)
				error(0, "");
		}
		else if (data->cmd->type[i] == DOUBLE_RIN)
		{
			if (data->cmd->redirection_file[i] == NULL)
			{
				lstclear_char(&data->cmd, free);
				error(1, "minishell: syntax error near unexpected token `newline'");
			}
			fd = open(data->cmd->redirection_file[i], O_CREAT | O_APPEND | O_WRONLY, 0644);
			if (fd < 0)
				error(0, "");
			if (dup2(fd, 1) < 0)
				error(0, "");
			if (close(fd) < 0)
				error(0, "");
		}
		else if (data->cmd->type[i] == SINGLE_ROUT)
		{
			if (data->cmd->redirection_file[i] == NULL)
			{
				lstclear_char(&data->cmd, free);
				error(1, "minishell: syntax error near unexpected token `newline'");
			}
			fd = open(data->cmd->redirection_file[i], O_RDONLY);
			if (fd < 0)
				error(0, "");
			if (dup2(fd, 0) < 0)
				error(0, "");
			if (close(fd) < 0)
				error(0, "");
		}
		else if (data->cmd->type[i] >= DOUBLE_ROUT)
			here_doc(data, i);
		if (ft_memcmp(data->cmd->content, "|\0", 2) == 0)
		{
			if (dup2(data->p[1], 1) < 0)
				error(0, "");
			if (dup2(data->fdd, 0) < 0)
				error(0, "");
			if (close(data->p[0]) < 0)
				error(0, "");
			if (close(data->p[1]) < 0)
				error(0, "");
		}
	}
}

void	exec(char **cmd, t_env *env)
{
	char	*tmp;

	if (!ft_memcmp(cmd[0], "<\0", 2) || !ft_memcmp(cmd[0], "<<\0", 3) || !ft_memcmp(cmd[0], ">\0", 2) || !ft_memcmp(cmd[0], ">>\0", 3) || !ft_memcmp(cmd[0], "|\0", 2))
	{
		free_all(cmd);
		exit(0);
	}
	tmp = get_path(env, cmd[0]);
	if (tmp == NULL)
		error(1, "minishell: Unable to find a path for the command");
	free(cmd[0]);
	cmd[0] = tmp;
	env->envp = env_list_to_tab(env);
	if (execve(cmd[0], cmd, env->envp) < 0)
	{
		puts("here");
		free_all(cmd);
		error(0, "");
	}
	exit(0);
}
