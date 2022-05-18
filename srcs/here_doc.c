/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:29:15 by psaulnie          #+#    #+#             */
/*   Updated: 2022/05/18 15:21:17 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*write_buffer_in_file(int type, t_env *env, int fd, char *buffer)
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
	t_here_doc	here_doc;

	here_doc.limiter = ft_strdup(data->cmd->redirection_file[current]);
	printf("[%s]\n", here_doc.limiter);
	here_doc.tmp_file_fd = open_file();
	while (buffer == NULL || (ft_memcmp(buffer, here_doc.limiter,
				ft_strlen(here_doc.limiter) + 1)
			|| data->env->limiter_check == 1))
	{
		buffer = while_here_doc(data, buffer, &here_doc, current);
		if (buffer == NULL || g_signal_flags)
			break ;
	}
	close(here_doc.tmp_file_fd);
	if (buffer && g_signal_flags == 0)
		free(buffer);
	free(here_doc.limiter);
}
