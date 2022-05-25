/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_envp2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:16:10 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/25 10:24:55 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	replace_or_add_line(t_miltn *data, char *var, t_env **env)
{
	if ((*env)->addon_env && (*env)->addon_env->content
		&& ft_memcmp((*env)->addon_env->content, var, ft_strlen(var)) == 0)
	{
		data->freeable = (*env)->addon_env;
		data->new_link = lstnew_char(data->line);
		data->tmp->next = data->new_link;
		data->new_link->next = (*env)->addon_env->next;
		(*env)->addon_env = data->tmp;
		free(data->freeable->content);
		free(data->freeable);
	}
	else
	{
		if (!lstadd_back_char(&(*env)->addon_env, lstnew_char(data->line)))
		{
			lstclear_char(&data->start, free);
			ft_putendl_fd("Malloc error", 2);
			free(data->line);
			return ;
		}
		(*env)->len_env++;
	}
	return ;
}

void	env_replace_line(t_env **env, char *var, char *value)
{
	t_miltn	data;

	data.start = (*env)->addon_env;
	data.line = ft_strjoin(var, value);
	if ((*env)->addon_env && (*env)->addon_env->content
		&& ft_memcmp((*env)->addon_env->content, var, ft_strlen(var)) == 0)
	{
		data.new_link = lstnew_char(data.line);
		data.new_link->next = (*env)->addon_env->next;
		(*env)->addon_env = data.new_link;
		return ;
	}
	while ((*env)->addon_env && (*env)->addon_env->content
		&& ft_memcmp((*env)->addon_env->content, var, ft_strlen(var)) != 0)
	{
		if (!(*env)->addon_env->next)
			break ;
		data.tmp = (*env)->addon_env;
		(*env)->addon_env = (*env)->addon_env->next;
	}
	replace_or_add_line(&data, var, env);
	if (data.start)
		(*env)->addon_env = data.start;
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
	char			*ln;
	t_list_char		*previous;

	if (!env->addon_env || !var)
		return ;
	ln = ft_strjoin(var, "=");
	if (!ln)
		exit_error_msg("Malloc error");
	start = env->addon_env;
	if (ft_memcmp(env->addon_env->content, ln, ft_strlen(ln)) == 0)
		start = unset_case_first_env_var(env);
	else
	{
		env->addon_env = find_env_var(env, ln);
		if (ft_memcmp(env->addon_env->next->content, ln, ft_strlen(ln)) == 0)
		{
			previous = env->addon_env->next;
			env->addon_env->next = env->addon_env->next->next;
			lstdelone_char(previous, free);
			env->len_env -= 1;
		}
	}
	free(ln);
	env->addon_env = start;
}
