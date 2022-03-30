/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 09:53:37 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/30 10:13:15 by psaulnie         ###   ########.fr       */
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
		{
			//protection malloc
			exit(0);
		}
		return (returned_env);
	}
	while (env.addon_env != NULL)
	{
		name = ft_strjoin(name, "=");
		if (!name)
		{
			//protection malloc
			exit(0);
		}
		if (ft_strnstr(env.addon_env->content, name, ft_strlen(name)))
		{
			returned_env = ft_strdup(ft_strnstr(env.addon_env->content,
						name, ft_strlen(name)) + ft_strlen(name) + 1);
			if (!returned_env)
			{
				//protection malloc
				exit(0);
			}
			break ;
		}
		env.addon_env = env.addon_env->next;
	}
	return (returned_env);
}
