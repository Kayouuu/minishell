/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_envp2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:16:10 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/09 16:18:06 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//tout mon probleme est ici je n'arrive a remplacer un maiont 
void	env_replace_line(t_env *env, char *var, char *value)
{
	char		*line;
	t_env		*start;
	t_list_char	*tmp;

	start = env;
	line = ft_strjoin(var, value);
	while (ft_memcmp(env->addon_env->content, var, ft_strlen(var)) != 0)
	{
		if (env->addon_env->next)
		{
			tmp = env->addon_env;
			env->addon_env = env->addon_env->next;
		}
		else
			break ;
	}
	if (ft_memcmp(env->addon_env->content, var, ft_strlen(var)) == 0)
	{
		;//tout doit ce passer ici je pense
	}
	else
	{
		if (!lstadd_back_char(&env->addon_env, lstnew_char(line)))
		{
			lstclear_char(&start->addon_env, free);
			ft_putendl_fd("Malloc error", 2);
			free(line);
			return ;
		}
	}
	env = start;
	free(line);
	return ;
}

static int	check_var(char *var)
{
	int	i;

	i = -1;
	while (var[++i])
		if (ft_isalnum((int)var[i]) == 0)
			return (1);
	return (0);
}

void	env_remove_line(t_env *env, char *var)
{
	t_env		*start;
	char		*line;
	// t_list_char	tmp;

	if (check_var(var) == 1)
	{
		ft_putendl_fd("minishell: unset: not a valid identifier", 2);
		return ;
	}
	line = ft_strjoin(var, "=");
	start = env;
	if (ft_memcmp(env->addon_env->content, line, ft_strlen(line)) == 0)
		;
	else
	{
		while (ft_memcmp(env->addon_env->next->content, line, ft_strlen(line)) != 0)
		{
			if (env->addon_env->next)
				env->addon_env = env->addon_env->next;
			else
				break ;
		}
	}
	free(line);
	return ;
}