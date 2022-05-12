/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_envp2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:16:10 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/12 10:54:13 by psaulnie         ###   ########.fr       */
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

static t_list_char	*unset_case_first_env_var(t_env *env)
{
	t_list_char	*previous;
	t_list_char	*start;

	previous = env->addon_env;
	env->addon_env = env->addon_env->next;
	start = env->addon_env;
	free(previous->content);
	free(previous);
	env->len_env -= 1;
	return (start);
}

static t_list_char	*find_env_var(t_env *env, char *line)
{
	while (ft_memcmp(env->addon_env->next->content, line,
			ft_strlen(line)) != 0)
	{
		if (env->addon_env->next->next)
			env->addon_env = env->addon_env->next;
		else
			break ;
	}
	return (env->addon_env);
}

void	env_remove_line(t_env *env, char *var)
{
	t_list_char		*start;
	char			*line;
	t_list_char		*previous;

	line = ft_strjoin(var, "=");
	if (!line)
		exit_error_msg("Malloc error");
	start = env->addon_env;
	if (ft_memcmp(env->addon_env->content, line, ft_strlen(line)) == 0)
		start = unset_case_first_env_var(env);
	else
	{
		env->addon_env = find_env_var(env, line);
		if (ft_memcmp(env->addon_env->next->content, line,
				ft_strlen(line)) == 0)
		{
			previous = env->addon_env->next;
			env->addon_env->next = env->addon_env->next->next;
			lstdelone_char(previous, free);
			env->len_env -= 1;
		}
	}
	free(line);
	env->addon_env = start;
	return ;
}
