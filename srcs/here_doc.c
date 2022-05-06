/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:29:15 by psaulnie          #+#    #+#             */
/*   Updated: 2022/05/06 15:29:32 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// static void	signalhandler(int status)
// {
// 	(void)status;
// }

static void	dupping_and_closing(int tmp_file_fd)
{
	if (close(tmp_file_fd) < 0)
		error(0, "");
	tmp_file_fd = open("/tmp/.minishell_heredoc", O_RDONLY);
	if (tmp_file_fd < 0)
		error(0, "");
	if (dup2(tmp_file_fd, 0) < 0)
		error(0, "");
	if (close(tmp_file_fd) < 0)
		error(0, "");
	if (unlink("/tmp/.minishell_heredoc") < 0)
		error(0, "");
}

static char	*write_buffer_in_file(int type, t_env env, int fd, char *buffer)
{
	if (type == 4)
		buffer = replace_env_var(buffer, env);
	if (buffer)
	{
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
	}
	return (buffer);
}

void	here_doc(t_data *data, int current)
{
	char	*buffer;
	char	*limiter;
	int		tmp_file_fd;

	limiter = data->cmd->redirection_file[current];
	buffer = NULL;
	tmp_file_fd = open("/tmp/.minishell_heredoc", O_WRONLY \
	| O_CREAT | O_TRUNC | O_CLOEXEC, 0644);
	if (tmp_file_fd < 0)
		error(0, "");
	while (buffer == NULL || ft_memcmp(buffer, limiter, ft_strlen(limiter) + 1))
	{
		if (buffer)
			free(buffer);
		// signal(SIGQUIT, utilise global var);
		buffer = readline("heredoc> ");
		if (!buffer)
			return ;
		buffer = write_buffer_in_file(data->cmd->type[current],
			*data->env, tmp_file_fd, buffer);
	}
	dupping_and_closing(tmp_file_fd);
	free(buffer);
}
