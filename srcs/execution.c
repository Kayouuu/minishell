/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:26:08 by psaulnie          #+#    #+#             */
/*   Updated: 2022/04/07 10:32:55 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	start_execution(t_list_char **cmd, t_env *env)
{
	int	fd;
	int	pid;

	pid = fork();
	while ((*cmd)->next != NULL)
	{
		special_case((*cmd), env->envp);
		if (ft_memcmp((*cmd)->content, ">>\0", 3))
		{
			(*cmd) = (*cmd)->next;
			fd = open((*cmd)->content, O_CREAT | O_APPEND | O_WRONLY, 0644);
			if (fd < 0)
				error(0, "");
			if (dup2(fd, 1) < 0)
				error(0, "");
			if (close(fd) < 0)
				error(0, "");
		}
		else if (ft_memcmp((*cmd)->content, ">\0", 2))
		{
			(*cmd) = (*cmd)->next;
			fd = open((*cmd)->content, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (fd < 0)
				error(0, "");
			if (dup2(fd, 1) < 0)
				error(0, "");
			if (close(fd) < 0)
				error(0, "");
		}
		else if (ft_memcmp((*cmd)->content, "<<\0", 3))/*here_doc avec delimiteur*/
			;
		else if (ft_memcmp((*cmd)->content, "<\0", 2))
		{
			(*cmd) = (*cmd)->next;
			fd = open((*cmd)->content, O_RDONLY);
			if (fd < 0)
				error(0, "");
			if (dup2(fd, 0) < 0)
				error(0, "");
			if (close(fd) < 0)
				error(0, "");
		}
		else
			exec(command_splitter((*cmd)->content), env);
		if ((*cmd)->next != NULL)
			(*cmd) = (*cmd)->next;
	}
}
