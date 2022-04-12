/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:36:28 by psaulnie          #+#    #+#             */
/*   Updated: 2022/04/12 17:37:15 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_cmd_special(char *cmd)
{
	if (!ft_memcmp(cmd, ">\0", 2)
		|| !ft_memcmp(cmd, "<\0", 2) || !ft_memcmp(cmd, ">>\0", 3)
		|| !ft_memcmp(cmd, "<<\0", 3))
		return (1);
	return (0);
}
