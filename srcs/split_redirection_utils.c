/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirection_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:04:51 by psaulnie          #+#    #+#             */
/*   Updated: 2022/05/02 16:55:24 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*redirection_split(char *cmd)
{
	size_t	i;
	char	c[2];
	char	*new_str;

	c[0] = cmd[0];
	c[1] = '\0';
	i = 0;
	while (cmd[i] && (cmd[i] == '<' || cmd[i] == '>'))
	{
		if (i == 0)
			new_str = ft_strdup(c);
		else
			new_str = ft_strjoin_gnl(new_str, c);
		if (!new_str)
			exit_error_msg("Malloc error");
		i++;
	}
	free(cmd);
	return (new_str);
}

t_index	skipper(t_index var, char *cmd)
{
	while (cmd != NULL && cmd[var.i])
	{
		if (cmd[var.i] == '\'' || cmd[var.i] == '"')
		{
			var.quote = cmd[var.i];
			var.i++;
			while (cmd[var.i] && cmd[var.i] != var.quote)
				var.i++;
			if (cmd[var.i])
				var.i++;
			var.quote = '0';
		}
		if (cmd[var.i] == '>' || cmd[var.i] == '<')
			break ;
		var.i++;
	}
	var.j = var.i;
	while (cmd != NULL && cmd[var.j] && (!ft_iswhitespace(cmd[var.j])
			&& (cmd[var.j] != '<' && cmd[var.j] != '>')))
		var.j++;
	return (var);
}

int	set_redirection_type(char *redirection)
{
	int	result;

	result = 0;
	if (!ft_memcmp(redirection, ">\0", 2))
		result = SINGLE_RIN;
	else if (!ft_memcmp(redirection, ">>\0", 3))
		result = DOUBLE_RIN;
	else if (!ft_memcmp(redirection, "<\0", 2))
		result = SINGLE_ROUT;
	else if (!ft_memcmp(redirection, "<<\0", 3))
		result = DOUBLE_ROUT;
	else
		printf("minishell: parse error near '%c'\n", redirection[0]);
	free(redirection);
	return (result);
}

int	type_setter(t_index var, t_list_char **cmd, t_list_char **start,
				int current)
{
	int		result;
	char	*str;
	char	*redirection;

	str = ft_stridup((*cmd)->content, var.i, var.j);
	if (!str)
	{
		(*cmd)->redirection_file[current + 1] = NULL;
		clear_list(start);
		ft_putendl_fd("Malloc error", 2);
		exit(0);
	}
	redirection = redirection_split(str);
	result = set_redirection_type(redirection);
	return (result);
}