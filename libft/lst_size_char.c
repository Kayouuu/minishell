/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_size_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:31:38 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/16 16:11:59 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	lstsize_char(t_list_char *lst)
{
	t_list_char	*start;
	int			i;

	i = 0;
	start = lst;
	if (lst == 0)
		return (0);
	if (lst->next == 0)
		return (1);
	while (lst->next != 0)
	{
		i++;
		lst = lst->next;
	}
	lst = start;
	return (i + 1);
}
