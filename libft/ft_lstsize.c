/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 15:28:12 by lbattest          #+#    #+#             */
/*   Updated: 2021/11/14 15:39:32 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;

	i = 0;
	if (lst == 0)
		return (0);
	if (lst->next == 0)
		return (1);
	while (lst->next != 0)
	{
		i++;
		lst = lst->next;
	}
	return (i + 1);
}
