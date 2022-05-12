/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:03:54 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/12 14:17:19 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	single_rin(t_data *data, int i)
{
	int	fd;

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
	return ;
}

static void	double_rin(t_data *data, int i)
{
	int	fd;

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
	return ;
}

static void	single_rout(t_data *data, int i)
{
	int	fd;

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
	return ;
}

static void	this_is_pipe(t_data *data)
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

void	redirection(t_data *data)
{
	int	i;

	i = -1;
	while (data->cmd->type[++i] != -1)
	{
		dprintf(2, "[%d] - [%s]\n", data->cmd->type[i], data->cmd->redirection_file[i]);
		if (data->cmd->type[i] == SINGLE_RIN)
			single_rin(data, i);
		else if (data->cmd->type[i] == DOUBLE_RIN)
			double_rin(data, i);
		else if (data->cmd->type[i] == SINGLE_ROUT)
			single_rout(data, i);
		else if (data->cmd->type[i] >= DOUBLE_ROUT)
			here_doc(data, i, NULL);
		if (ft_memcmp(data->cmd->content, "|\0", 2) == 0)
			this_is_pipe(data);
	}
}
