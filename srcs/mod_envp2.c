/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_envp2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:16:10 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/11 17:49:42 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//tout mon probleme est ici je n'arrive a remplacer un maiont 
void	env_replace_line(t_env **env, char *var, char *value)
{
	char		*line;
	t_list_char	*start;
	t_list_char	*tmp;
	t_list_char	*new_link;
	t_list_char	*freeable;

	start = (*env)->addon_env;
	line = ft_strjoin(var, value);
	if (ft_memcmp((*env)->addon_env->content, var, ft_strlen(var)) == 0)
	{
		new_link = lstnew_char(line);
		new_link->next = (*env)->addon_env->next;
		(*env)->addon_env = new_link;
		return ;
	}
	while (ft_memcmp((*env)->addon_env->content, var, ft_strlen(var)) != 0)
	{
		if ((*env)->addon_env->next)
		{
			tmp = (*env)->addon_env;
			(*env)->addon_env = (*env)->addon_env->next;
		}
		else
			break ;
	}
	if (ft_memcmp((*env)->addon_env->content, var, ft_strlen(var)) == 0)
	{
		freeable = (*env)->addon_env;
		new_link = lstnew_char(line);
		tmp->next = new_link;
		new_link->next = (*env)->addon_env->next;
		(*env)->addon_env = tmp;
		free(freeable);
	}
	else
	{
		if (!lstadd_back_char(&(*env)->addon_env, lstnew_char(line)))
		{
			lstclear_char(&start, free);
			ft_putendl_fd("Malloc error", 2);
			free(line);
			return ;
		}
		(*env)->len_env++;
	}
	(*env)->addon_env = start;
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
	t_list_char		*start;
	char			*line;
	// t_list_char	tmp;

	if (check_var(var) == 1)
	{
		ft_putendl_fd("minishell: unset: not a valid identifier", 2);
		return ;
	}
	line = ft_strjoin(var, "=");
<<<<<<< HEAD
	if (!line)
		exit_error_msg("Malloc error");
	start = env;
=======
	start = env->addon_env;
>>>>>>> d453af1bf2021e490bbbd4cac779d9d544ad5333
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
	env->addon_env = start;
	return ;
}