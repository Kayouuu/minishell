/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:29:15 by psaulnie          #+#    #+#             */
/*   Updated: 2022/05/18 10:27:56 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	signalhandler(int status)
{
	(void)status;
	g_signal_flags = 1;
	close(0);
}

static char	*write_buffer_in_file(int type, t_env *env, int fd, char *buffer)
{
	char	*tmp;

	if (type == 4)
	{
		tmp = ft_strdup(buffer);
		if (!tmp)
			exit(0);
		buffer = replace_env_var(buffer, *env);
		if (ft_memcmp(tmp, buffer, ft_strlen(tmp)))
			env->limiter_check = 1;
		free(tmp);
	}
	if (buffer)
	{
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
	}
	return (buffer);
}

static int	open_file(void)
{
	int	fd;

	fd = open("/tmp/.minishell_heredoc", O_WRONLY \
	| O_CREAT | O_TRUNC | O_CLOEXEC, 0644);
	if (fd < 0)
		error(0, "");
	return (fd);
}

void	here_doc(t_data *data, int current, char *buffer)
{
	char	*limiter;
	int		tmp_file_fd;

	limiter = data->cmd->redirection_file[current];
	if (limiter == NULL)
		return ;
	else
		return ;
	tmp_file_fd = open_file();
	while (buffer == NULL || (ft_memcmp(buffer, limiter, ft_strlen(limiter) + 1)
			|| data->env->limiter_check == 1))
	{
		data->env->limiter_check = 0;
		if (buffer)
			free(buffer);
		signal(SIGINT, signalhandler);
		signal(SIGQUIT, SIG_IGN);
		buffer = readline("heredoc> ");
		if (!buffer || g_signal_flags)
			break ;
		if ((ft_memcmp(buffer, limiter, ft_strlen(limiter) + 1)))
			buffer = write_buffer_in_file(data->cmd->type[current],
					data->env, tmp_file_fd, buffer);
	}
	close(tmp_file_fd);
	if (buffer && g_signal_flags == 0)
		free(buffer);
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
