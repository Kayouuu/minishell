/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 12:21:31 by psaulnie          #+#    #+#             */
/*   Updated: 2022/05/18 12:27:47 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	signalhandler(int status)
{
	(void)status;
	g_signal_flags = 1;
	close(0);
}

int	while_here_doc(t_data *data, char *buffer, t_here_doc *here_doc,
	int current)
{
	data->env->limiter_check = 0;
	if (buffer)
		free(buffer);
	signal(SIGINT, signalhandler);
	signal(SIGQUIT, SIG_IGN);
	buffer = readline("heredoc> ");
	if (!buffer || g_signal_flags)
		return (1);
	if ((ft_memcmp(buffer, here_doc->limiter,
				ft_strlen(here_doc->limiter) + 1)))
		buffer = write_buffer_in_file(data->cmd->type[current],
				data->env, here_doc->tmp_file_fd, buffer);
	return (0);
}

void	double_rout(void)
{
	int	fd;

	fd = open("/tmp/.minishell_heredoc", O_RDONLY);
	if (fd < 0)
		error(0, "");
	if (dup2(fd, 0) < 0)
		error(0, "");
	if (close(fd) < 0)
		error(0, "");
}
