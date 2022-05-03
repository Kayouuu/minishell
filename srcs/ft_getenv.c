/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 09:53:37 by psaulnie          #+#    #+#             */
/*   Updated: 2022/05/03 15:54:58 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_getenv(t_env env, char *name)
{
	char	*returned_env;
	char	*var;

	var = getenv(name);
	returned_env = NULL;
	if (var)
	{
		returned_env = ft_strdup(var);
		if (!returned_env)
			return (NULL);
		return (returned_env);
	}
	while (env.addon_env != NULL)
	{
		name = ft_strjoin_gnl(name, "=");
		if (!name)
			return (NULL);
		if (ft_strnstr(env.addon_env->content, name, ft_strlen(name)))
		{
			returned_env = ft_strdup(ft_strnstr(env.addon_env->content,
						name, ft_strlen(name) + 1) + ft_strlen(name) + 1);
			if (!returned_env)
				return (NULL);
			break ;
		}
		env.addon_env = env.addon_env->next;
	}
	return (returned_env);
}
