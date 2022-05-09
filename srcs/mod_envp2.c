/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_envp2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:16:10 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/09 14:19:03 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	env_replace_line(t_env *env, char *var, char *value)
{
	char	*line;
	t_env	*start;

	start = env;
	line = ft_strjoin(var, value);
	while (ft_memcmp(env->addon_env->content, var, ft_strlen(var)) != 0)
	{
		if (env->addon_env->next)
			env->addon_env = env->addon_env->next;
		else
			break ;
	}
	if (ft_memcmp(env->addon_env->content, var, ft_strlen(var)) == 0)
	{
		free(env->addon_env->content);
		env->addon_env->content = malloc(sizeof(char *) * (ft_strlen(line) + 1));
		env->addon_env->content = line;
	}
	else
	{
		if (!lstadd_back_char(&env->addon_env, lstnew_char(line)))
		{
			lstclear_char(&start->addon_env, free);
			ft_putendl_fd("Malloc error", 2);
			return ;
		}
	}
	return ;
}

// void	env_remove_line(t_env *env, char *line)
// {
	
// }