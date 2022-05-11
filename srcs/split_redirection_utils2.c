/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirection_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 13:56:14 by psaulnie          #+#    #+#             */
/*   Updated: 2022/05/11 11:43:47 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_index	iteration_nbr_quoting(char *cmd, t_index var)
{
	if (cmd[var.i] == '\'' && (var.quote == '0'))
		var.quote = '\'';
	if (cmd[var.i] == '"' && (var.quote == '0'))
		var.quote = '"';
	if (var.quote != '0')
	{
		var.i++;
		while (cmd[var.i] && cmd[var.i] != var.quote)
			var.i++;
		if (cmd[var.i])
			var.i++;
		var.quote = '0';
		var.quotes = 0;
	}
	return (var);
}

int	iteration_nbr(char *cmd)
{
	t_index	var;
	int		nbr;

	var.i = -1;
	var.quote = '0';
	var.quotes = 0;
	nbr = 0;
	while (cmd != NULL && cmd[++var.i]
		&& (cmd[var.i] != '|' && var.quote == '0'))
	{
		if (cmd[var.i + 1] != '\0' && cmd[var.i + 1] == cmd[var.i])
			var.i++;
		var = iteration_nbr_quoting(cmd, var);
		if ((cmd[var.i] == '<' || cmd[var.i] == '>') && (var.quote == '0'))
			nbr++;
		if (!cmd[var.i])
			break ;
	}
	return (nbr);
}

static t_index	loop_var_skipper(t_index var, t_list_char **cmd)
{
	while (((*cmd)->content[var.j]
			&& (!ft_iswhitespace((*cmd)->content[var.j]))))
	{
		if ((*cmd)->content[var.j] == '\'' || (*cmd)->content[var.j] == '"')
		{
			var.quote = (*cmd)->content[var.j];
			while ((*cmd)->content[var.j]
				&& (*cmd)->content[var.j] != var.quote)
				var.j++;
			var.quote = '0';
		}
		if ((*cmd)->content[var.j] == '<' || (*cmd)->content[var.j] == '>')
			break ;
		if ((*cmd)->content[var.j])
			var.j++;
	}
	return (var);
}

t_index	var_skipper(t_index var, t_list_char **cmd)
{
	var.i = 0;
	var.quote = '0';
	var.quotes = 0;
	var = skipper(var, (*cmd)->content);
	while (var.i < (int)ft_strlen((*cmd)->content) && (*cmd)->content[var.j]
		&& (*cmd)->content[var.j + 1] == (*cmd)->content[var.j])
		var.j++;
	if ((*cmd)->content[var.j])
		var.j++;
	if (var.j < (int)ft_strlen((*cmd)->content) && (*cmd)->content[var.j])
			var = loop_var_skipper(var, cmd);
	return (var);
}
