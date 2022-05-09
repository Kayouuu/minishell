/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 09:53:37 by psaulnie          #+#    #+#             */
/*   Updated: 2022/05/09 15:25:59 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_getenv(t_env env, char *name)
{
	char	*returned_env;

	returned_env = NULL;
	name = ft_strjoin_gnl(name, "=");
	if (!name)
		return (NULL);
	while (env.addon_env != NULL)
	{
		if (ft_strnstr(env.addon_env->content, name, ft_strlen(name)))
		{
			returned_env = ft_strdup(ft_strnstr(env.addon_env->content,
						name, ft_strlen(name)) + ft_strlen(name));
			if (!returned_env)
				return (NULL);
			break ;
		}
		env.addon_env = env.addon_env->next;
	}
	free(name);
	return (returned_env);
}
