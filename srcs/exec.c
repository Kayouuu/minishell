/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:04:40 by lbattest          #+#    #+#             */
/*   Updated: 2022/04/11 12:20:45 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	redirection(t_list_char *cmd)
{
	int	fd;

	if (!ft_memcmp(cmd->content, ">>\0", 3))
	{
		printf(">>\n");
		cmd = cmd->next;
		fd = open(cmd->content, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (fd < 0)
			error(0, "");
		if (dup2(fd, 1) < 0)
			error(0, "");
		if (close(fd) < 0)
			error(0, "");
		cmd = cmd->next;
	}
	else if (!ft_memcmp(cmd->content, ">\0", 2))
	{
		// printf(">\n");
		cmd = cmd->next;
		fd = open(cmd->content, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd < 0)
			error(0, "");
		if (dup2(fd, 1) < 0)
			error(0, "");
		if (close(fd) < 0)
			error(0, "");
		cmd = cmd->next;
	}
	// else if (!ft_memcmp((*cmd)->content, "<<\0", 3))/*here_doc avec delimiteur*/
	// 	;
	else if (!ft_memcmp(cmd->content, "<\0", 2))
	{
		printf("<\n");
		cmd = cmd->next;
		fd = open(cmd->content, O_RDONLY);
		if (fd < 0)
			error(0, "");
		if (dup2(fd, 0) < 0)
			error(0, "");
		if (close(fd) < 0)
			error(0, "");
		cmd = cmd->next;
	}
	return ;
}

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
	exit(0);
}
 