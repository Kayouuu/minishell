/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirection_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 13:56:14 by psaulnie          #+#    #+#             */
/*   Updated: 2022/05/02 17:56:15 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	iteration_nbr_quoting(char *cmd, t_index var)
{
	if (cmd[var.i] == '\'' && (var.quote == '0'))
		var.quote = '\'';
	if (cmd[var.i] == '"' && (var.quote == '0'))
		var.quote = '"';
	return (var.quote);
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
		var.quote = iteration_nbr_quoting(cmd, var);
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
		if ((cmd[var.i] == '<' || cmd[var.i] == '>') && (var.quote == '0'))
			nbr++;
		if (!cmd[var.i])
			break ;
	}
	return (nbr);
}
