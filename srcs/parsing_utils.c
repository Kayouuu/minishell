/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 10:31:45 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/21 17:38:52 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	skip_whitespace(char *cmd, int i)
{
	while (cmd[i] == ' ' || cmd[i] == '\t'
		|| cmd[i] == '\n' || cmd[i] == '\v'
		|| cmd[i] == '\f' || cmd[i] == '\r')
		i++;
	return (i);
}

int	is_useless(char *command)
{
	int	i;
	int	is_useless;

	i = 0;
	is_useless = 1;
	while (command[i])
	{
		if (!(command[i] == ' ' || command[i] == '\t' || command[i] == '\n'
				|| command[i] == '\n' || command[i] == '\v'
				|| command[i] == '\f' || command[i] == '\r'))
			is_useless = 0;
		i++;
	}
	return (is_useless);
}
