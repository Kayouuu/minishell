/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:03:54 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/20 18:25:09 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	single_rin(t_data *data, int i)
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
	{
		perror("minishell");
		return (0);
	}
	if (data->cmd->next == NULL)
		data->has_redirection = 1;
	if (dup2(fd, 1) < 0)
		error(0, "");
	if (close(fd) < 0)
		error(0, "");
	return (1);
}

static int	double_rin(t_data *data, int i)
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
	{
		perror("minishell");
		return (0);
	}
	if (data->cmd->next == NULL)
		data->has_redirection = 1;
	if (dup2(fd, 1) < 0)
		error(0, "");
	if (close(fd) < 0)
		error(0, "");
	return (1);
}

static int	single_rout(t_data *data, int i)
{
	int	fd;

	if (data->cmd->redirection_file[i] == NULL)
	{
		lstclear_char(&data->cmd, free);
		error(1, "minishell: syntax error near unexpected token `newline'");
	}
	fd = open(data->cmd->redirection_file[i], O_RDONLY);
	if (fd < 0)
	{
		perror("minishell");
		return (0);
	}
	if (dup2(fd, 0) < 0)
		error(0, "");
	if (close(fd) < 0)
		error(0, "");
	return (1);
}

static void	this_is_pipe(t_data *data, int j)
{
	if (j > 0)
	{
		if (dup2(data->fdd[0], 0) < 0)
			error(0, "");
		close(data->fdd[0]);
		close(data->fdd[1]);
	}
	if (data->cmd->next && ft_memcmp(data->cmd->next->content, "|\0", 2) == 0)
	{
		if (dup2(data->p[1], 1) < 0)
			error(0, "");
		if (close(data->p[1]) < 0)
			error(0, "");
		if (close(data->p[0]) < 0)
			error(0, "");
	}
}

int	redirection(t_data *data, int j)
{
	int	i;

	i = -1;
	this_is_pipe(data, j);
	while (data->cmd->type[++i] != -1)
	{
		if (data->cmd->type[i] == SINGLE_RIN)
		{
			if (!single_rin(data, i))
				return (0);
		}
		else if (data->cmd->type[i] == DOUBLE_RIN)
		{
			if (!double_rin(data, i))
				return (0);
		}
		else if (data->cmd->type[i] == SINGLE_ROUT)
		{
			if (!single_rout(data, i))
				return (0);
		}
		else if (data->cmd->type[i] >= DOUBLE_ROUT)
			double_rout();
	}
	return (1);
}
