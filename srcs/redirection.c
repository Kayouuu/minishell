/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:03:54 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/17 15:25:51 by psaulnie         ###   ########.fr       */
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
	fd = open(data->cmd->redirection_file[i],
			O_CREAT | O_TRUNC | O_WRONLY, 0644);
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
	fd = open(data->cmd->redirection_file[i],
			O_CREAT | O_APPEND | O_WRONLY, 0644);
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
	if (close(data->p[1]) < 0)
		error(0, "");
	if (close(data->p[0]) < 0)
		error(0, "");
}

void	redirection(t_data *data, int j)
{
	int	i;

	i = -1;
	if (j > 0)
	{
		if (dup2(data->fdd[0], 0) < 0)
			error(0, "");
		close(data->fdd[0]);
		close(data->fdd[1]);
	}
	if (data->cmd->next && ft_memcmp(data->cmd->next->content, "|\0", 2) == 0)
		this_is_pipe(data);
	while (data->cmd->type[++i] != -1)
	{
		if (data->cmd->type[i] == SINGLE_RIN)
			single_rin(data, i);
		else if (data->cmd->type[i] == DOUBLE_RIN)
			double_rin(data, i);
		else if (data->cmd->type[i] == SINGLE_ROUT)
			single_rout(data, i);
		else if (data->cmd->type[i] >= DOUBLE_ROUT)
			here_doc(data, i, NULL);
	}
}
