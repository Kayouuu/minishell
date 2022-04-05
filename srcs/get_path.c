/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:53:18 by lbattest          #+#    #+#             */
/*   Updated: 2022/04/05 14:40:33 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	*free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (0);
}

static char	*get_envpath(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_memcmp(envp[i], "PATH=", 5) == 0)
			return (&envp[i][5]);
		i++;
	}
	return (NULL);
}

/*
	this function take envp and a char * with the name of the command(cat, ...)
	In the end exe is a char * with the path + the command(/bin/cat, ...)
*/

char	*get_path(char **envp, char *cmd)
{
	char	*exe;
	char	*path;
	char	**tmp;
	int		i;

	path = get_envpath(envp);
	if (!path)
		return (NULL);
	i = 0;
	tmp = ft_split(path, ':');
	while (tmp[i])
	{
		exe = ft_strjoin_mod(tmp[i], cmd);
		if (access(exe, X_OK | F_OK) == 0)
		{
			free_all(tmp);
			return (exe);
		}
		i++;
	}
	free_all(tmp);
	return (NULL);
}
